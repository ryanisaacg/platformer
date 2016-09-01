//-*-C++-*-
#pragma once

#include "SDL.h"

#include "optional.h"
#include "tilemap.h"
#include "vector2.h"

#include "window.h"

enum class ControlType { NONE, PLAYER };
enum class Alignment { NONE, PLAYER, ENEMY };

struct Entity {
public:
	int x, y, width, height, health;
	Vector2 speed;
	SDL_Texture *texture;
	ControlType control;
	int fire_cooldown = 0, facing = 1;
	float gravity = 0;
	Alignment alignment;
	bool projectile;
	Entity();
	Entity(int x, int y, int width, int height, SDL_Texture *texture, bool projectile = false, 
		ControlType type = ControlType::NONE);
	const SDL_Rect sdl_bounds() const;
	const Rect bounds() const;
	void move();
	void render(const Window &window) const;
	template<typename T>
	void move(const TileMap<T> map) {
		auto rect = bounds();
		auto prev_speed = speed;
		if(projectile) {
			Vector2 xspeed(speed.x, 0);
			Vector2 yspeed(0, speed.y);
			map.shape_slide(rect, xspeed, rect, xspeed);
			map.shape_slide(rect, yspeed, rect, yspeed);
			if(xspeed.x != speed.x) speed.x *= -1;
			if(yspeed.y != speed.y) speed.y *= -1;
		} else {
			map.shape_slide(rect, speed, rect, speed);
		}
		x = rect.x;
		y = rect.y;
		width = rect.width;
		height = rect.height;
	}
};

