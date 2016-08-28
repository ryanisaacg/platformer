#include "pcontroller.h"
#include "physics.h"

PlayerController::PlayerController(const Keyboard &keyboard, 
	const TileMap<Optional<Entity>> &map, Entity &player) :
	keyboard(keyboard), map(map), player(player) {}

void PlayerController::update() const{
	player.speed.x = 0;
	if(keyboard[SDLK_d])
		player.speed.x = 3;
	if(keyboard[SDLK_a])
		player.speed.x = -3;
	if(keyboard[SDLK_w] && supported(map, player))
		player.speed.y = -10;
}
	
