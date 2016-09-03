#include "controller.h"

#include <algorithm>

#include "entity.h"

Controller::Controller(Keyboard &keyboard, Mouse &mouse, State &state, SDL_Texture *bullet) : 
	keyboard(keyboard), state(state), bullet(bullet), mouse(mouse) {}

float clamp(float value, float low, float high) {
	return std::min(high, std::max(low, value));
}

void Controller::update() {
	mouse.update();
	for(int i = 0; i < state.entities.size(); i++) {
		auto &entity = state.entities[i];
		switch(entity.control) {
		case ControlType::PLAYER:
			if(keyboard[SDL_SCANCODE_D]) {
				entity.speed.x = clamp(entity.speed.x + 0.5, 0, 5);
				entity.facing = 1;
			} else if(keyboard[SDL_SCANCODE_A]) {
				entity.speed.x = clamp(entity.speed.x - 0.5, -5, 0);
				entity.facing = -1;
			} else {
				entity.speed.x += -entity.speed.x * 0.5;
			}
			entity.speed.x = clamp(entity.speed.x, -6, 6);
			if(keyboard[SDL_SCANCODE_W]) {
				if(/*!jumpedLastFrame && */state.supported(entity)) {
					entity.speed.y = -10;
				}
				jumpedLastFrame = true;
			} else {
				jumpedLastFrame = false;
			}
			if(mouse.left && entity.fire_cooldown == 0 && hasSaw) {
				auto speed = Vector2(mouse.x - entity.bounds->getX(), mouse.y - entity.bounds->getY()).set_length(12);
				auto &bullet = state.spawn(Circle(entity.bounds->getX() + 24, entity.bounds->getY() + 24, 24), this->bullet, true);
				bullet.speed = speed;
				entity.fire_cooldown = 10;
				bullet.alignment = Alignment::PLAYER;
				hasSaw = false;
			}
			break;
		}
	}
}
	
