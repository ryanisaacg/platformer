#ifndef ENTITY_H_
#define ENTITY_H_

#include "SDL.h"

#include "optional.h"
#include "tilemap.h"
#include "vector2.h"

#include "texture.h"
#include "window.h"

struct Entity {
	int x, y, width, height;
	Vector2 speed;
	Optional<Texture> texture;
	Entity();
	Entity(int x, int y, int width, int height, Optional<Texture> texture);
	const SDL_Rect sdl_bounds() const;
	const Rect bounds() const;
	void move();
	void render(const Window &window) const;
	template<typename T>
	void move(const TileMap<T> map) {
		auto rect = bounds();
		map.rect_move(rect, speed, rect, speed);
		x = rect.x;
		y = rect.y;
		width = rect.width;
		height = rect.height;
	}
};
#endif
