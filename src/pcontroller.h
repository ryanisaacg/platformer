//-*-C++-*-
#pragma once

#include "optional.h"
#include "tilemap.h"

#include "entity.h"
#include "keyboard.h"

class PlayerController {
public:
	PlayerController(const Keyboard &keyboard, const TileMap<Optional<Entity>> &map, Entity &player);
	void update() const;
private:
	const Keyboard &keyboard;
	const TileMap<Optional<Entity>> &map;
	Entity &player;
};
