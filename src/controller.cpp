#include "controller.h"

#include "entity.h"

Controller::Controller(const Keyboard &keyboard, State &state) : keyboard(keyboard), state(state) {}

void Controller::update() {
	for(int i = 0; i < state.entities.size(); i++) {
		auto &entity = state.entities[i];
		switch(entity.control) {
		case ControlType::PLAYER:
			entity.speed.x = 0;
			if(keyboard[SDL_SCANCODE_D])
				entity.speed.x = 3;
			if(keyboard[SDL_SCANCODE_A]) 
				entity.speed.x = -3;
			if(keyboard[SDL_SCANCODE_W]) {
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
	
