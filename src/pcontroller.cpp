#include "pcontroller.h"
#include "physics.h"

PlayerController::PlayerController(const Keyboard &keyboard, 
	const TileMap<Optional<Entity>> &map, Entity &player) :
	keyboard(keyboard), map(map), player(player), jumpedLastFrame(false) {}

void PlayerController::update() {
	player.speed.x = 0;
	if(keyboard[SDLK_d])
		player.speed.x = 3;
	if(keyboard[SDLK_a])
		player.speed.x = -3;
	if(keyboard[SDLK_w]) {
		if(!jumpedLastFrame && supported(map, player)) {
			player.speed.y = -10;
		}
		jumpedLastFrame = true;
	} else {
		jumpedLastFrame = false;
	}
}
	
