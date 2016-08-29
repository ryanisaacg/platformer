#include <algorithm>

#include "controller.h"

#include "entity.h"

Controller::Controller(const Keyboard &keyboard, State &state) : keyboard(keyboard), state(state) {}

float clamp(float value, float low, float high) {
	return std::min(high, std::max(low, value));
}

void Controller::update() {
	for(int i = 0; i < state.entities.size(); i++) {
		auto &entity = state.entities[i];
		switch(entity.control) {
		case ControlType::PLAYER:
			if(keyboard[SDL_SCANCODE_RIGHT]) {
				entity.speed.x = clamp(entity.speed.x + 0.5, 0, 5);
				entity.facing = 1;
			} else if(keyboard[SDL_SCANCODE_LEFT]) {
				entity.speed.x = clamp(entity.speed.x - 0.5, -5, 0);
				entity.facing = -1;
			} else {
				entity.speed.x += -entity.speed.x * 0.5;
			}
			entity.speed.x = clamp(entity.speed.x, -6, 6);
			if(keyboard[SDL_SCANCODE_F]) {
				if(!jumpedLastFrame && state.supported(entity)) {
					entity.speed.y = -10;
				}
				jumpedLastFrame = true;
			} else {
				jumpedLastFrame = false;
			}
			if(keyboard[SDL_SCANCODE_D] && entity.fire_cooldown == 0) {
				auto &bullet = state.spawn(Rect(entity.x, entity.y, entity.width, entity.height), entity.texture, true);
				bullet.speed.x = entity.facing * 31;
				entity.fire_cooldown = 10;
				entity.speed.x -= entity.facing * 3;
			}
			break;
		}
	}
}
	
