//-*-C++-*-
#pragma once

#include "SDL.h"

#include "keyboard.h"
#include "mouse.h"
#include "state.h"

class Controller {
public:
	Controller(Keyboard &keyboard, Mouse &mouse, State &state, SDL_Texture *bullet);
	void update();
private:
	bool jumpedLastFrame, clickedLastFrame;
	Keyboard &keyboard;
	Mouse &mouse;
	State &state;
	SDL_Texture *bullet;
	Entity *saw = nullptr;
};
