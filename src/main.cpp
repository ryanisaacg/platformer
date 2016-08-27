#include <iostream>

#include "optional.h"
#include "SDL.h"
#undef main
#include "tilemap.h"

#include "physics.h"
#include "rect.h"



int main() {
	TileMap<Optional<Entity>> map(640, 480, 32);
	map[Vector2(0, 0)] = Entity(0, 480, 32, 32, nullptr);
	auto ent = Entity(0, 0, 32, 32, nullptr);
	std::vector<Entity> entities;
	entities.push_back(ent);
	for(int i = 0; i < 30; i++)
		update(map, entities);
	std::cout << entities[0].y;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Platformer", 10, 10, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Delay(1000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

