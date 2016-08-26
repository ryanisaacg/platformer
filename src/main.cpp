#include "SDL.h"
#include "tilemap.h"
#include "rect.h"

#undef main

int main() {
	TileMap<rect> map(640, 480, 32);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Platformer", 10, 10, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Delay(1000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

