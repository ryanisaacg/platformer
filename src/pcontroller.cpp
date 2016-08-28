#include "pcontroller.h"

#include "entity.h"

PlayerController::PlayerController(const Keyboard &keyboard, State &state) : keyboard(keyboard), state(state) {}

void PlayerController::update() {
	for(int i = 0; i < state.entities.size(); i++) {
		auto &entity = state.entities[i];
		switch(entity.control) {
		case ControlType::PLAYER:
			entity.speed.x = 0;
			if(keyboard[SDLK_d])
				entity.speed.x = 3;
			if(keyboard[SDLK_a]) 
				entity.speed.x = -3;
			if(keyboard[SDLK_w]) {
				if(!jumpedLastFrame && state.supported(entity)) {
					entity.speed.y = -10;
				}
				jumpedLastFrame = true;
			} else {
				jumpedLastFrame = false;
			}
			break;
		}
	}
}
	
