#ifndef ENTITY_H_
#define ENTITY_H_

#include "SDL.h"
#include "tilemap.h"
#include "vector2.h"

struct Entity {
	int x, y, width, height;
	Vector2 speed;
	SDL_Texture *texture;
	Entity();
	Entity(int x, int y, int width, int height, SDL_Texture *texture);
	const SDL_Rect sdl_bounds() const;
	const Rect bounds() const;
	void move();
	template<typename T>
	void move(const TileMap<T> map) {
		auto rect = bounds();
		map.move(rect, speed, rect, texture);
		x = rect.x;
		y = rect.y;
		width = rect.width;
		height = rect.height;
	}
};
#endif
