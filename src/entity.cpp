#include "entity.h"

Entity::Entity() : Entity(Rect(0, 0, 0, 0), nullptr) {}

Entity::Entity(Rect rect, SDL_Texture *texture, bool projectile, ControlType control) : texture(texture), 
speed(0, 0), projectile(projectile), control(control), health(1), alignment(Alignment::NONE) {
	bounds = new Rect(rect.x, rect.y, rect.width, rect.height);
}

Entity::Entity(Circle circ, SDL_Texture *texture, bool projectile, ControlType control) : texture(texture), 
speed(0, 0), projectile(projectile), control(control), health(1), alignment(Alignment::NONE) {
	bounds = new Circle(circ.x, circ.y, circ.radius);
}

Entity::~Entity() {
	delete bounds;
}

const SDL_Rect Entity::sdl_bounds() const {
	SDL_Rect rect;
	rect.x = (int)bounds->left();
	rect.y = (int)bounds->top();
	rect.w = (int)(bounds->right() - bounds->left());
	rect.h = (int)(bounds->bottom() - bounds->top());
	return rect;
}

void Entity::move() {
	bounds->setX(bounds->getX() + speed.x);
	bounds->setY(bounds->getY() + speed.y);
}

void Entity::render(const Window &window) const {
	window.render(texture, bounds);
}
