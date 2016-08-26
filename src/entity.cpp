#include "entity.h"

Entity::Entity(int x, int y, int width, int height, SDL_Texture *texture)
	: x(x), y(y), width(width), height(height), texture(texture) {}


SDL_Rect Entity::bounds() {
	SDL_Rect rect = {x, y, width, height};
	return rect;
}
