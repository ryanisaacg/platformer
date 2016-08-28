//-*-C++-*-
#pragma once

#include <unordered_set>

#include "SDL.h"

//Stores key state
class Keyboard {
public:
	const bool process(const SDL_Event &e); //Processses an event and returns if anything was changed
	const bool operator[](const SDL_Scancode key) const;
private:
	std::unordered_set<int> pressed;
};
