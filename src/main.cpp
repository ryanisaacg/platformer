#include <iostream>
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

#undef main
int main() {
	string title = "Platformer";
	auto window = Window(title.c_str(), 640, 480);
	TileMap<Optional<Entity>> map(640, 480, 32);
	vector<Entity> entities;
	Keyboard keyboard;
	auto texture = window.load_texture("../img/red.png");
	map[Vector2(0, 448)] = Entity(0, 448, 32, 32, texture);
	auto ent = Entity(0, 0, 32, 32, texture);
	entities.push_back(ent);
	auto controller = PlayerController(keyboard, map, entities[0]);
	bool run_loop = true;
	while(run_loop) {
		//EVENT POLLING
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) run_loop = false;
			else keyboard.process(e);
		}
		//STATE UPDATE
		controller.update();
		update(map, entities);
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
		SDL_Delay(16);
	}
	return 0;
}

