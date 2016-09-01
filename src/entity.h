//-*-C++-*-
#pragma once

#include "SDL.h"

#include "optional.h"
#include "physical.h"
#include "tilemap.h"
#include "vector2.h"

#include "window.h"

enum class ControlType { NONE, PLAYER };
enum class Alignment { NONE, PLAYER, ENEMY };

struct Entity {
public:
	Physical *bounds;
	Vector2 speed;
	SDL_Texture *texture;
	ControlType control;
	int fire_cooldown = 0, facing = 1, health = 0;
	float gravity = 0;
	Alignment alignment;
	bool projectile;
	Entity();
	Entity(Rect rect, SDL_Texture *texture, bool projectile = false, ControlType type = ControlType::NONE);
	Entity(Circle circ, SDL_Texture *texture, bool projectile = false, ControlType type = ControlType::NONE);
	~Entity();
	const SDL_Rect sdl_bounds() const;
	void move();
	void render(const Window &window) const;
	template<typename T>
	void move(const TileMap<T> map) {
		auto prev_speed = speed;
		if(projectile) {
			Vector2 xspeed(speed.x, 0);
			Vector2 yspeed(0, speed.y);
			map.shape_slide(bounds, xspeed, bounds, xspeed);
			map.shape_slide(bounds, yspeed, bounds, yspeed);
			if(xspeed.x != speed.x) speed.x *= -1;
			if(yspeed.y != speed.y) speed.y *= -1;
		} else {
			map.shape_slide(bounds, speed, bounds, speed);
		}
	}
};

