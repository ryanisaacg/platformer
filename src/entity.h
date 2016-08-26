#ifndef ENTITY_H_
#define ENTITY_H_

#include "SDL.h"

struct Entity {
	int x, y, width, height;
	SDL_Texture *texture;
	Entity(int x, int y, int width, int height, SDL_Texture *texture);
	SDL_Rect bounds();
};
#endif
