#include "physics.h"

static void gravity(TileMap<Entity> map, std::vector<Entity> entities);

void update(TileMap<Entity> map, std::vector<Entity> entities) {
	gravity(map, entities);
	for(auto &entity : entities) {
		entity.move(map);
	}
}
	
	
static void gravity(TileMap<Entity> map, std::vector<Entity> entities) {
	for(auto &entity : entities) {
		auto bounds = entity.bounds();
		bounds.y += 1;
		if(map.free(bounds)) {
			entity.speed.y += 2;
		}
	}
}
	
