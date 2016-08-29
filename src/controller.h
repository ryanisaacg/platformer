//-*-C++-*-
#pragma once

#include "SDL.h"

#include "keyboard.h"
#include "state.h"

class Controller {
public:
	Controller(const Keyboard &keyboard, State &state, SDL_Texture *bullet);
	void update();
private:
	bool jumpedLastFrame;
	const Keyboard &keyboard;
	State &state;
	SDL_Texture *bullet;
};
