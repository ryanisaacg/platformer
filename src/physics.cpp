#include <iostream>

#include "physics.h"

static void gravity(TileMap<Optional<Entity>> map, std::shared_ptr<std::vector<Entity>> entities);

void update(TileMap<Optional<Entity>> map, std::shared_ptr<std::vector<Entity>> entities) {
	gravity(map, entities);
	for(auto &entity : *entities) {
		entity.move(map);
	}
}
	
	
static void gravity(TileMap<Optional<Entity>> map, std::shared_ptr<std::vector<Entity>> entities) {
	for(auto& entity : *entities) {
		auto bounds = entity.bounds();
		bounds.y += 1;
		if(map.free(bounds)) {
			entity.speed.y += 2;
		}
	}
}
	
