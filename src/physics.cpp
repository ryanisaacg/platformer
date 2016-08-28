#include "physics.h"

using namespace std;

static void gravity(const TileMap<Optional<Entity>> &map, vector<Entity> &entities);

void update(const TileMap<Optional<Entity>> &map, vector<Entity> &entities) {
	gravity(map, entities);
	for(auto &entity : entities) {
		entity.move(map);
	}
}
	
	
static void gravity(const TileMap<Optional<Entity>> &map, vector<Entity> &entities) {
	for(auto& entity : entities) {
		if(!supported(map, entity)) {
			entity.speed.y += 0.5f;
		}
	}
}

bool supported(const TileMap<Optional<Entity>> &map, const Entity &test) {
	auto bounds = test.bounds();
	bounds.y += 1;
	return !map.free(bounds);
}
