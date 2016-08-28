#include "pcontroller.h"

PlayerController::PlayerController(const Keyboard &keyboard, 
	const State &state, Entity &player) :
	keyboard(keyboard), state(state), player(player), jumpedLastFrame(false) {}

void PlayerController::update() {
	player.speed.x = 0;
	if(keyboard[SDLK_d])
		player.speed.x = 3;
	if(keyboard[SDLK_a]) 
		player.speed.x = -3;
	if(keyboard[SDLK_w]) {
		if(!jumpedLastFrame && state.supported(player)) {
			player.speed.y = -10;
		}
		jumpedLastFrame = true;
	} else {
		jumpedLastFrame = false;
	}
}
	
