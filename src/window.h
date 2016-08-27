#ifndef WINDOW_H_
#define WINDOW_H_

#include "SDL.h"

#include "rect.h"
#include "texture.h"

class Window {
public:
	Window(const char *name, int width, int height);
	~Window();
	void render(const Texture texture, Rect source, Rect dest) const;
	void render(const Texture texture, Rect dest) const;
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	friend class Texture;
};

#endif
