//-*-C++-*-
#pragma once

#include "SDL.h"
#include "arcade-physics.h"

#include "entity.h"
#include "tilemap.h"

struct Level;

struct State {
	State(Level &parent, int width, int height, int tile_size);
	Entity &spawn(const Rect region, SDL_Texture *texture, bool contact_death = false, ControlType control = ControlType::NONE);
	Entity &spawn(const Circle region, SDL_Texture *texture, bool contact_death = false, ControlType control = ControlType::NONE);
	void place_tile(const Vector2 point, SDL_Texture *texture);
	void update();
	void cleanup();
	bool supported(const Entity &entity) const;
	template <typename T>
	void do_to_entities(T t) {
		for(int i = 0; i < entities.size(); i++)
			t(entities[i]);
	}
	Level &parent;
	TileMap<Optional<Entity>> map;
	std::vector<Entity> entities;
	const int TILE_SIZE;
};
	
#include "level.h"
