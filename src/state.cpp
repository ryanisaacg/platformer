#include <algorithm>

#include "state.h"

State::State(int width, int height) : map(width, height, State::TILE_SIZE), entities() {}

Entity& State::spawn(Rect region, SDL_Texture *texture, bool contact_death, ControlType control) {
	auto ent = Entity(region.x, region.y, region.width, region.height, texture, contact_death, control);
	entities.push_back(ent);
	return entities[entities.size() - 1];
}
void State::place_tile(Vector2 point, SDL_Texture *texture) {
	map[point] = Entity(point.x, point.y, State::TILE_SIZE, State::TILE_SIZE, texture);
}
void State::update() {
	for(auto& entity : entities) {
		if(!supported(entity)) {
			entity.speed.y += 0.5f;
		}
		entity.move(map);
		if(entity.fire_cooldown > 0)
			entity.fire_cooldown -= 1;
	}
	entities.erase(std::remove_if(entities.begin(), entities.end(),
		[](auto &entity) { return entity.health <= 0; }),
	entities.end());
}
bool State::supported(const Entity &entity) const {
	auto bounds = entity.bounds();
	bounds.y += 1;
	return !map.free(bounds);
}
