#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "window.h"

static SDL_Rect to_sdl(const Rect input);

Window::Window(const char *name, int width, int height) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Window::render(const Texture &texture, Rect source, Rect dest) const {
	SDL_Rect src = to_sdl(source);
	SDL_Rect dst = to_sdl(dest);
	SDL_RenderCopy(renderer, texture.texture, &src, &dst);
}

void Window::render(const Texture &texture, Rect dest) const {
	SDL_Rect dst = to_sdl(dest);
	SDL_RenderCopy(renderer, texture.texture, nullptr, &dst);
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
}

static SDL_Rect to_sdl(const Rect input) {
	SDL_Rect rect;
	rect.x = (int)input.x;
	rect.y = (int)input.y;
	rect.w = (int)input.width;
	rect.h = (int)input.height;
	return rect;
}

void Window::start() {
	SDL_RenderClear(renderer);
}

void Window::end() {
	SDL_RenderPresent(renderer);
}
