#include "keyboard.h"

const bool Keyboard::process(const SDL_Event &e) {
	switch(e.type) {
	case SDL_KEYDOWN:
		keys[e.key.keysym.sym] = true;
		break;
	case SDL_KEYUP:
		keys[e.key.keysym.sym] = false;
		break;
	default:
		return false; //No key event was processed
	}
	return true;
}

const bool Keyboard::operator[](const SDL_Keycode key) const {
	return keys[key];
}

const bool Keyboard::operator[](const SDL_Scancode key) const {
	return keys[key];
}
