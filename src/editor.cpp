#include "editor.h"

Editor::Editor(Level &level, Mouse &mouse, Keyboard &keyboard) : level(level), mouse(mouse), 
	keyboard(keyboard) {
	state = EditorState::Block;
}

void Editor::update() {
	mouse.update();
	if(keyboard[SDL_SCANCODE_1])
		state = EditorState::Block;
	if(keyboard[SDL_SCANCODE_2])
		state = EditorState::Player;
	if(keyboard[SDL_SCANCODE_3])
		state = EditorState::Enemy;
	switch(state) {
	case EditorState::Block:
		if(mouse.left)
			level.place_tile(Vector2(mouse.x, mouse.y));
		else if(mouse.right)
			level.remove_tile(Vector2(mouse.x, mouse.y));
		break;
	case EditorState::Player:
		if(mouse.left || mouse.right)
			level.set_player_position(Vector2(mouse.x, mouse.y));
		break;
	case EditorState::Enemy:
		if(mouse.left)
			level.add_enemy(Vector2(mouse.x, mouse.y));
		else if(mouse.right)
			level.remove_enemy(Vector2(mouse.x, mouse.y));
		break;
	}
}
