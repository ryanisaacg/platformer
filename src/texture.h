#ifndef TEXTURE_H_
#define TEXTURE_H_

class Window;

#include "window.h"

struct Texture {
	Texture(Window window, const char *filename);
	~Texture();
	SDL_Texture *texture;
	const int width;
	const int height;
};
#endif
