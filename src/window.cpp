#include "SDL.h"

#include "window.h"

Window::Window(char *name, int width, int height) {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
}

Window::~Window() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
