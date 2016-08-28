//-*-C++-*-
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "SDL.h"

//Stores key state
class Keyboard {
public:
	const bool process(const SDL_Event &e); //Processses an event and returns if anything was changed
	const bool operator[](const SDL_Keycode key) const;
	const bool operator[](const SDL_Scancode key) const;
private:
	bool keys[261] = {false}; //There are 261 SDL key/scan codes
};
#endif
