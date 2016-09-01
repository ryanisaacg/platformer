#include "SDL.h"
#include "SDL_image.h"

#include "window.h"

static SDL_Rect to_sdl(const Entity &dest);

Window::Window(const char *name, int width, int height) : textures() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0x0);
}

void Window::render(const Entity &entity) const {
	SDL_Rect dst = to_sdl(entity);
	SDL_RenderCopy(renderer, entity.texture, nullptr, &dst);
}

SDL_Surface* Window::load_surface(const char *filename) {
	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(filename);
	if (loadedSurface == nullptr)
		std::cout << "Unable to load image " << filename << "! SDL_image Error: " << IMG_GetError() << std::endl;
	else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, SDL_GetWindowSurface(window)->format, 0);
		if (optimizedSurface == nullptr) {
			std::cout << "Unable to optimize image " << filename << "! SDL Error: " << SDL_GetError();
			optimizedSurface = loadedSurface;
		} else {
			SDL_FreeSurface(loadedSurface);
		}
	}
	return optimizedSurface;
}

SDL_Texture* Window::load_texture(const char *filename) {
	SDL_Surface *surface = load_surface(filename);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if(texture == nullptr) {
		std::cout << "Unable to create texture from " << filename << "! SDL Error: " << SDL_GetError() << std::endl;
	} else {
		textures.push_back(texture);
	}
	return texture;
}

Window::~Window() {
	for(auto &tex : textures) 
		SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
}

static SDL_Rect to_sdl(const Entity &dest) {
	SDL_Rect rect;
	rect.x = (int)dest.bounds->left();
	rect.y = (int)dest.bounds->top();
	rect.w = (int)(dest.bounds->right() - dest.bounds->left());
	rect.h = (int)(dest.bounds->bottom() - dest.bounds->top());
	return rect;
}

void Window::start() {
	SDL_RenderClear(renderer);
}

void Window::end() {
	SDL_RenderPresent(renderer);
}
