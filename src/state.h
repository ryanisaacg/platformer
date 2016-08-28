//-*-C++-*-
#pragma once

#include "SDL.h"

#include "optional.h"
#include "rect.h"
#include "vector2.h"

#include "entity.h"
#include "tilemap.h"

struct State {
	static const int TILE_SIZE = 32;
	State(int width, int height);
	Entity &spawn(const Rect region, SDL_Texture *texture);
	void place_tile(const Vector2 point, SDL_Texture *texture);
	void update();
	bool supported(const Entity &entity) const;
	template <typename T>
	void do_to_entities() {
		for(int i = 0; i < entities.size(); i++)
			T(entities[i]);
	}
	TileMap<Optional<Entity>> map;
	std::vector<Entity> entities;
};
	
