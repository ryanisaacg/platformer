#include "controller.h"

#include <algorithm>

#include "entity.h"

Controller::Controller(Keyboard &keyboard, Mouse &mouse, State &state, SDL_Texture *bullet) : 
	keyboard(keyboard), state(state), bullet(bullet), mouse(mouse) {}

float clamp(float value, float low, float high) {
	return std::min(high, std::max(low, value));
}

//TODO: Avoid using pointer for Saw
void Controller::update() {
	mouse.update();
	for(int i = 0; i < state.entities.size(); i++) {
		auto &entity = state.entities[i];
		bool found;
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
			if(mouse.left && !clickedLastFrame && entity.fire_cooldown == 0) {
				clickedLastFrame = true;
				found = false;
				for(int i = 0; i < state.entities.size() && !found; i++) {
					auto &e = state.entities[i];
					if(e.projectile && e.alignment == Alignment::PLAYER) {
						float dst_x = entity.bounds->getX() - e.bounds->getX();
						float dst_y = entity.bounds->getY() - e.bounds->getY();
						float dst2 = dst_x * dst_x + dst_y * dst_y;
						constexpr int max_dst = 60 * 60;
						if(dst2 < max_dst) {						
							entity.fire_cooldown = 60;
							e.health = 0;
						}
						found = true;
					}
				}
				if(!found) {
					auto speed = Vector2(mouse.x - entity.bounds->getX(), mouse.y - entity.bounds->getY()).set_length(12);
					auto step = speed.set_length(50);
					if(state.map.free(entity.bounds->getX() + step.x, entity.bounds->getY() + step.y, 48, 48)) {
						auto &bullet = state.spawn(Circle(entity.bounds->getX() + step.x + 24, entity.bounds->getY() + step.y + 24, 24), 
							this->bullet, true);
						bullet.speed = speed;
						entity.fire_cooldown = 60;
						bullet.alignment = Alignment::PLAYER;
					}
				}
			}
			if(clickedLastFrame && !mouse.left)
				clickedLastFrame = false;
			break;
		case ControlType::ENEMY:
			for(int i = 0; i < state.entities.size() && !found; i++) {
				auto &e = state.entities[i];
				if(e.control == ControlType::PLAYER) {
					entity.speed.x = 3 * get_sign(e.bounds->getX() - entity.bounds->getX());
				}
			}
		}
	}
}
	
