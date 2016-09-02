#include <algorithm>
#include <utility>

#include "state.h"

State::State(int width, int height) : map(width, height, State::TILE_SIZE), entities() {}

Entity& State::spawn(Rect region, SDL_Texture *texture, bool contact_death, ControlType control) {
	entities.push_back(Entity(region, texture, contact_death, control));
	return entities[entities.size() - 1];
}

Entity& State::spawn(Circle region, SDL_Texture *texture, bool contact_death, ControlType control) {
	entities.push_back(Entity(region, texture, contact_death, control));
	return entities[entities.size() - 1];
}
void State::place_tile(Vector2 point, SDL_Texture *texture) {
	map[point] = std::move(Entity(Rect(point.x, point.y, State::TILE_SIZE, State::TILE_SIZE), texture));
}
void State::update() {
	for(auto& entity : entities) {
		if(!supported(entity)) {
			entity.speed.y += entity.gravity;
		}
		entity.move(map);
		if(entity.projectile) {
			for(auto &other : entities) {
				auto ent_bounds = entity.bounds;
				auto other_bounds = other.bounds;
				if(&other != &entity && other.alignment != Alignment::NONE && 
					other.alignment != entity.alignment && other_bounds->overlaps(ent_bounds.get())) {
					other.health -= 1;
					entity.speed = entity.speed.scale(-1);
				}
			}
		} else if(entity.fire_cooldown > 0)
			entity.fire_cooldown -= 1;
	}
	entities.erase(std::remove_if(entities.begin(), entities.end(),
		[](auto &entity) { return entity.health <= 0; }),
	entities.end());
}
bool State::supported(const Entity &entity) const {
	entity.bounds->setY(entity.bounds->getY() + 1);
	bool free = !map.free(entity.bounds.get());
	entity.bounds->setY(entity.bounds->getY() - 1);
	return free;
}
