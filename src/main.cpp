#include <iostream>
#include <vector>

#include "SDL.h"

#include "optional.h"
#include "tilemap.h"

#include "physics.h"
#include "rect.h"
#include "window.h"

using namespace std;

#undef main
int main() {
	TileMap<Optional<Entity>> map(640, 480, 32);
	map[Vector2(0, 448)] = Entity(0, 448, 32, 32, Optional<Texture>());
	auto ent = Entity(0, 0, 32, 32, Optional<Texture>());
	vector<Entity> entities;
	entities.push_back(ent);
	for(int i = 0; i < 30; i++)
		update(map, entities);
	cout << entities[0].y << std::endl;
	string title = "Platformer";
	auto window = Window(title.c_str(), 640, 480);
	SDL_Delay(1000);
	return 0;
}

