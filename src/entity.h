#ifndef ENTITY_H_
#define ENTITY_H_

#include "SDL.h"
#include "tilemap.h"
#include "vector2.h"

struct Entity {
	int x, y, width, height;
	Vector2 speed;
	SDL_Texture *texture;
	Entity(int x, int y, int width, int height, SDL_Texture *texture);
	const SDL_Rect bounds() const;
	void move();
	template<typename T>
	void move(TileMap<T> map) {
		
	}
};
#endif
