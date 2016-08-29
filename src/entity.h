//-*-C++-*-
#pragma once

#include "SDL.h"

#include "optional.h"
#include "tilemap.h"
#include "vector2.h"

#include "window.h"

enum class ControlType { NONE, PLAYER };

struct Entity {
public:
	int x, y, width, height, health;
	Vector2 speed;
	SDL_Texture *texture;
	ControlType control;
	int fire_cooldown = 0, facing = 1;
	Entity();
	Entity(int x, int y, int width, int height, SDL_Texture *texture, bool die_on_contact = false, 
		ControlType type = ControlType::NONE);
	const SDL_Rect sdl_bounds() const;
	const Rect bounds() const;
	void move();
	void render(const Window &window) const;
	template<typename T>
	void move(const TileMap<T> map) {
		auto rect = bounds();
		auto prev_speed = speed;
		map.rect_slide(rect, speed, rect, speed);
		x = rect.x;
		y = rect.y;
		width = rect.width;
		height = rect.height;
		if(die_on_contact && (speed.x != prev_speed.x || speed.y != prev_speed.y))
			health = 0;
	}
private:
	bool die_on_contact;
};

