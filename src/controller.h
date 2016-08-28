//-*-C++-*-
#pragma once

#include "keyboard.h"
#include "state.h"

class Controller {
public:
	Controller(const Keyboard &keyboard, State &state);
	void update();
private:
	bool jumpedLastFrame;
	const Keyboard &keyboard;
	State &state;
};
