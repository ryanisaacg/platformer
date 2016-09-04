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
			if(mouse.left && entity.fire_cooldown == 0) {
				if(saw == nullptr) {
					auto speed = Vector2(mouse.x - entity.bounds->getX(), mouse.y - entity.bounds->getY()).set_length(12);
					auto step = speed.set_length(50);
					if(state.map.free(entity.bounds->getX() + step.x, entity.bounds->getY() + step.y, 48, 48)) {
						auto &bullet = state.spawn(Circle(entity.bounds->getX() + step.x + 24, entity.bounds->getY() + step.y + 24, 24), 
							this->bullet, true);
						saw = &bullet;
						auto ptr = bullet.bounds;
						saw->bounds = ptr;
						bullet.speed = speed;
						entity.fire_cooldown = 60;
						bullet.alignment = Alignment::PLAYER;
					}
				} else {
					float dst_x = entity.bounds->getX() - saw->bounds->getX();
					float dst_y = entity.bounds->getY() - saw->bounds->getY();
					float dst2 = dst_x * dst_x + dst_y * dst_y;
					constexpr int max_dst = 60 * 60;
					if(dst2 < max_dst) {						
						entity.fire_cooldown = 60;
						saw->health = 0;
						saw = nullptr;
					}
				}
			}
			break;
		}
	}
}
	
