#include <iostream>
#include <thread>
#include <vector>

#include "SDL.h"

#include "optional.h"
#include "tilemap.h"

#include "keyboard.h"
#include "pcontroller.h"
#include "physics.h"
#include "rect.h"
#include "window.h"

using namespace std;

bool run_loop = true;

TileMap<Optional<Entity>> map(640, 480, 32);
vector<Entity> entities;

void update_loop() {
	while(run_loop) {
		//STATE UPDATE
		auto ticks = SDL_GetTicks();
		update(map, entities);
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
	map[Vector2(0, 448)] = Entity(0, 448, 32, 32, texture);
	auto ent = Entity(0, 0, 32, 32, texture);
	entities.push_back(ent);
	auto controller = PlayerController(keyboard, map, entities[0]);
	auto update_thread = thread(update_loop);
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
		controller.update();
		//RENDER CODE
		window.start();
		for(auto &ent : entities)
			ent.render(window);
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

