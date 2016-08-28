#include "entity.h"

Entity::Entity() : Entity(0, 0, 0, 0, nullptr) {}

Entity::Entity(int x, int y, int width, int height, SDL_Texture *texture, bool die_on_contact, ControlType control) : x(x), y(y), 
	width(width), height(height), texture(texture), speed(0, 0), die_on_contact(die_on_contact), control(control), health(1) {}


const SDL_Rect Entity::sdl_bounds() const {
	SDL_Rect rect = {x, y, width, height};
	return rect;
}

const Rect Entity::bounds() const {
	return Rect(x, y, width, height);
}

void Entity::move() {
	x += speed.x;
	y += speed.y;
}

void Entity::render(const Window &window) const {
	window.render(texture, bounds());
}
