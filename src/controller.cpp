#include "controller.h"

#include "entity.h"

Controller::Controller(const Keyboard &keyboard, State &state) : keyboard(keyboard), state(state) {}

void Controller::update() {
	for(int i = 0; i < state.entities.size(); i++) {
		auto &entity = state.entities[i];
		switch(entity.control) {
		case ControlType::PLAYER:
			entity.speed.x = 0;
			if(keyboard[SDL_SCANCODE_RIGHT]) {
				entity.speed.x = 3;
				entity.facing = 1;
			}
			if(keyboard[SDL_SCANCODE_LEFT]) {
				entity.speed.x = -3;
				entity.facing = -1;
			}
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
				bullet.speed.x = entity.facing * 10;
				entity.fire_cooldown = 10;
			}
			break;
		}
	}
}
	
