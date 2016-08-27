#include "SDL.h"
#include "SDL_image.h"

#include "texture.h"
#include "window.h"

Texture::Texture(Window window, const char *filename) {
	SDL_Surface *surface = IMG_Load(filename);
	width = surface->w;
	height = surface->h;
	texture = SDL_CreateTextureFromSurface(window.renderer, surface);
	SDL_FreeSurface(surface);
}

Texture::Texture() : texture(nullptr), width(0), height(0) {}

Texture& Texture::operator=(const Texture& other) {
	texture = other.texture;
	width = other.width;
	height = other.height;
	return *this;
}

Texture::~Texture() {
	SDL_DestroyTexture(texture);
}


