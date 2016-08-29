#include <iostream>
#include <thread>
#include <vector>

#include "SDL.h"

#include "optional.h"
#include "tilemap.h"

#include "keyboard.h"
#include "controller.h"
#include "rect.h"
#include "state.h"
#include "window.h"

using namespace std;

bool run_loop = true;

State state(640, 480);

void update_loop(Controller controller) {
	while(run_loop) {
		//STATE UPDATE
		auto ticks = SDL_GetTicks();
		state.update();
		controller.update();
		auto elapsed = SDL_GetTicks() - ticks;
		if(elapsed > 16) continue;
		SDL_Delay(16 - elapsed);
	}
}

#undef main
int main() {
	string title = "Platformer";
	auto window = Window(title.c_str(), 640, 480);
	Keyboard keyboard;
	auto texture = window.load_texture("../img/red.png");
	state.place_tile(Vector2(0, 448), texture);
	auto &player = state.spawn(Rect(0, 0, 32, 32), texture, false, ControlType::PLAYER);
	state.spawn(Rect(200, 0, 32, 32), texture, true);
	auto update_thread = thread(update_loop, Controller(keyboard, state, window.load_texture("../img/bullet.png")));
	int frames = 0;
	float avg_framerate = 0;
	while(run_loop) {
		auto start = SDL_GetTicks();
		//EVENT POLLING
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) run_loop = false;
			else keyboard.process(e);
		}
		//RENDER CODE
		window.start();
		for(auto &ent : state.entities)
			ent.render(window);
		auto map = state.map;
		for(int x = 0; x < map.width; x += map.square_size) {
			for(int y = 0; y < map.height; y += map.square_size) {
				auto square = map[Vector2(x, y)];
				if(square) {
					(*square).render(window);
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

