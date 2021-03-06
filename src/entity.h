//-*-C++-*-
#pragma once

#include <memory>

#include "SDL.h"
#include "arcade-physics.h"

enum class ControlType { NONE, PLAYER, ENEMY };
enum class Alignment { NONE, PLAYER, ENEMY };

struct Entity {
public:
	std::shared_ptr<Physical> bounds;
	Vector2 speed;
	SDL_Texture *texture;
	ControlType control;
	int fire_cooldown = 0, facing = 1, health = 0;
	float gravity = 0;
	Alignment alignment;
	bool projectile, flies, walks;
	Entity();
	Entity(Rect rect, SDL_Texture *texture, bool projectile = false, ControlType type = ControlType::NONE);
	Entity(Circle circ, SDL_Texture *texture, bool projectile = false, ControlType type = ControlType::NONE);
	const SDL_Rect sdl_bounds() const;
	void move();
	template<typename T>
	void move(const TileMap<T> &map) {
		auto prev_speed = speed;
		if(projectile) {
			Vector2 xspeed(speed.x, 0);
			Vector2 yspeed(0, speed.y);
			map.shape_slide(bounds.get(), xspeed, bounds.get(), xspeed);
			map.shape_slide(bounds.get(), yspeed, bounds.get(), yspeed);
			if(xspeed.x != speed.x) speed.x *= -1;
			if(yspeed.y != speed.y) speed.y *= -1;
		} else {
			map.shape_slide(bounds.get(), speed, bounds.get(), speed);
		}
	}
};

