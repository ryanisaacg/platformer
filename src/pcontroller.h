//-*-C++-*-
#pragma once

#include "entity.h"
#include "keyboard.h"
#include "state.h"

class PlayerController {
public:
	PlayerController(const Keyboard &keyboard, const State &state, Entity &player);
	void update();
private:
	bool jumpedLastFrame;
	const Keyboard &keyboard;
	const State &state;
	Entity &player;
};
