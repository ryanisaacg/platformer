//-*-C++-*-
#pragma once

#include <unordered_set>

#include "SDL.h"

#include "mutex.h"

//Stores key state
class Keyboard {
public:
	const bool process(const SDL_Event &e); //Processses an event and returns if anything was changed
	const bool operator[](const SDL_Scancode key);
private:
	std::unordered_set<int> pressed;
	std::mutex mutex;
};
