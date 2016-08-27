#ifndef WINDOW_H_
#define WINDOW_H_

#include "SDL.h"

class Window {
public:
	Window(char *name, int width, int height);
	~Window();
private:
	SDL_Window *window;
};

#endif
