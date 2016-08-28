#ifndef TEXTURE_H_
#define TEXTURE_H_

class Window;

#include "window.h"

struct Texture {
	Texture(Window &window, const char *filename);
	Texture();
	~Texture();
	Texture& operator=(const Texture& other);
	SDL_Texture *texture;
	int width;
	int height;
};
#endif
