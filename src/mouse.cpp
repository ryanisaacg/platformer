#include "mouse.h"

#include "SDL.h"

Mouse::Mouse() : Mouse(1, 1) {
	update();
}

Mouse::Mouse(float xscale, float yscale) : xscale(xscale), yscale(yscale) {
	update();
}

void Mouse::update() {
	auto buttonmask = SDL_GetMouseState(&x, &y);
	x = (int)(x / xscale);
	y = (int)(y / yscale);
	left = buttonmask & SDL_BUTTON_LMASK;
	right = buttonmask & SDL_BUTTON_RMASK;
	middle = buttonmask & SDL_BUTTON_MMASK;
	x1 = buttonmask & SDL_BUTTON_X1MASK;
	x2 = buttonmask & SDL_BUTTON_X2MASK;
}
