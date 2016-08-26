#include "SDL.h"

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Platformer", 10, 10, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Delay(1000);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

