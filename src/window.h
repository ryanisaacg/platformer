#ifndef WINDOW_H_
#define WINDOW_H_

#include "SDL.h"

#include "rect.h"

class Window {
public:
	Window(const char *name, int width, int height);
	~Window();
	SDL_Surface* load_surface(const char *filename);
	SDL_Texture* load_texture(const char *filename);
	void render(SDL_Texture *texture, Rect source, Rect dest) const;
	void render(SDL_Texture *texture, Rect dest) const;
	void start();
	void end();
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	friend class Texture;
};

#endif
