#include "mouse.h"

#include "SDL.h"

Mouse::Mouse() {
	update();
}

void Mouse::update() {
	auto buttonmask = SDL_GetMouseState(&x, &y);
	left = buttonmask & SDL_BUTTON_LMASK;
	right = buttonmask & SDL_BUTTON_RMASK;
	middle = buttonmask & SDL_BUTTON_MMASK;
	x1 = buttonmask & SDL_BUTTON_X1MASK;
	x2 = buttonmask & SDL_BUTTON_X2MASK;
}