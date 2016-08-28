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
	string title = "Platformer";
	auto window = Window(title.c_str(), 640, 480);
	TileMap<Optional<Entity>> map(640, 480, 32);
	map[Vector2(0, 448)] = Entity(0, 448, 32, 32, Optional<Texture>());
	auto ent = Entity(0, 0, 32, 32, Optional<Texture>(Texture(window, "../img/red.png")));
	vector<Entity> entities;
	entities.push_back(ent);
	bool run_loop = true;
	while(run_loop) {
		update(map, entities);
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				run_loop = false;
			}
		}
		window.start();
		for(auto &ent : entities)
			ent.render(window);
		window.end();
		SDL_Delay(16);
	}
	return 0;
}

