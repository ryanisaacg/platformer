//-*-C++-*-
#pragma once

#include "entity.h"
#include "keyboard.h"
#include "state.h"

class PlayerController {
public:
	PlayerController(const Keyboard &keyboard, State &state);
	void update();
private:
	bool jumpedLastFrame;
	const Keyboard &keyboard;
	State &state;
};
