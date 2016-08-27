#include "texture.h"
#include "window.h"

Texture(Window window, const char *filename) {
	SDL_Surface *surface = IMG_Load(path);
	width = surface->w;
	height = surface->h;
	texture = SDL_TextureFromSurface(window.renderer, surface);
	SDL_FreeSurface(surface);
}

~Texture() {
	SDL_DestroyTexture(texture);
}


