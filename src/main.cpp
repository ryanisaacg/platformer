#include <iostream>
#include <thread>
#include <vector>

#include "SDL.h"
#include "arcade-physics.h"

#include "controller.h"
#include "editor.h"
#include "keyboard.h"
#include "level.h"
#include "mouse.h"
#include "mutex.h"
#include "rect.h"
#include "window.h"

using namespace std;

std::mutex mtx, keymtx;
bool run_loop = true;

const int width = 1920,
          height = 1080;

Window window("Platformer", width, height);
Level level("../data/test", width, height, window);
Keyboard keyboard;
Mouse mouse(window.x_scale, window.y_scale);
Editor editor(level, mouse, keyboard);
Controller controller(keyboard, mouse, level.state, window.load_texture("../img/saw.png"));

void update_loop(Controller controller) {
	bool is_editor = true, esc_last = false;
	while(run_loop) {
		//STATE UPDATE
		auto ticks = SDL_GetTicks();
		if(is_editor) {
			auto tmp = acquire(mtx);
			auto key = acquire(keymtx);
			editor.update();
		} else {
			auto tmp = acquire(mtx);
			level.state.update();
			level.state.cleanup();
			{
				auto key = acquire(keymtx);
				controller.update();
			}
			level.state.cleanup();
		}
		{
			auto key = acquire(keymtx);
			if(keyboard[SDL_SCANCODE_ESCAPE]) {
				if(!esc_last)
					is_editor = !is_editor;
				esc_last = true;
			} else {
				esc_last = false;
			}
		}
		auto elapsed = SDL_GetTicks() - ticks;
		if(elapsed > 16) continue;
		SDL_Delay(16 - elapsed);
	}
}

#undef main
int main() {
	auto update_thread = thread(update_loop, controller);
	int frames = 0;
	float avg_framerate = 0;
	while(run_loop) {
		auto start = SDL_GetTicks();
		//EVENT POLLING
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) run_loop = false;
			else {
				auto key = acquire(keymtx);
				keyboard.process(e);
			}
		}
		//RENDER CODE
		window.start();
		{
			auto tmp = acquire(mtx);
			for(auto &ent : level.state.entities)
				window.render(ent);
			auto &map = level.state.map;
			for(int x = 0; x < map.width; x += map.square_size) {
				for(int y = 0; y < map.height; y += map.square_size) {
					auto square = map[Vector2(x, y)];
					if(square) {
						window.render(*square);
					}
				}
			}
		}
		window.end();
		auto end = SDL_GetTicks();
		frames += 1;
		float total = frames * avg_framerate;
		total += end - start;
		avg_framerate = total / frames;
	}
	update_thread.join();
	cout << "Average framerate: " << 1000 / avg_framerate << endl;
	return 0;
}

