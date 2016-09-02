#include "keyboard.h"

const bool Keyboard::process(const SDL_Event &e) {
	auto mtx = acquire(mutex);
	switch(e.type) {
	case SDL_KEYDOWN:
		pressed.insert(e.key.keysym.scancode);
		break;
	case SDL_KEYUP:
		pressed.erase(e.key.keysym.scancode);
		break;
	default:
		return false; //No key event was processed
	}
	return true;
}
const bool Keyboard::operator[](const SDL_Scancode key) {
	auto mtx = acquire(mutex);
	return pressed.count(key) > 0;
}
