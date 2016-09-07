//-*-C++-*-
#pragma once

#include <vector>

#include "SDL.h"

#include "entity.h"

class Window {
public:
	Window(const char *name, int width, int height);
	~Window();
	SDL_Surface* load_surface(const char *filename);
	SDL_Texture* load_texture(const char *filename);
	void render(const Entity &dest) const;
	void start();
	void end();
	float x_scale, y_scale;
private:
	SDL_Rect to_sdl(const Entity &dest) const;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::vector<SDL_Texture*> textures;
};
