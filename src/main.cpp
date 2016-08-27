#include <iostream>
#include <vector>

#include "optional.h"
#include "SDL.h"
#undef main
#include "tilemap.h"

#include "physics.h"
#include "rect.h"

using namespace std;

int main() {
	TileMap<Optional<Entity>> map(640, 480, 32);
	map[Vector2(0, 448)] = Entity(0, 448, 32, 32, nullptr);
	auto ent = Entity(0, 0, 32, 32, nullptr);
	vector<Entity> entities;
	entities.push_back(ent);
	for(int i = 0; i < 30; i++)
		update(map, entities);
	cout << entities[0].y << std::endl;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Platformer", 10, 10, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Delay(1000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

