#include "SDL.h"
#include "SDL_image.h"

#include "window.h"

Window::Window(const char *name, int width, int height) : textures() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mode.w, mode.h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_SetWindowGrab(window, SDL_TRUE);
	x_scale = width / (float)mode.w;
	y_scale = height / (float) mode.h;
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
	return loadedSurface;
}

SDL_Texture* Window::load_texture(const char *filename) {
	SDL_Surface *surface = load_surface(filename);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
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

SDL_Rect Window::to_sdl(const Entity &dest) const {
	SDL_Rect rect;
	rect.x = (int)(dest.bounds->left() * x_scale);
	rect.y = (int)(dest.bounds->top() * y_scale);
	rect.w = (int)((dest.bounds->right() - dest.bounds->left()) * x_scale);
	rect.h = (int)((dest.bounds->bottom() - dest.bounds->top()) * y_scale);
	return rect;
}

void Window::start() {
	SDL_RenderClear(renderer);
}

void Window::end() {
	SDL_RenderPresent(renderer);
}
