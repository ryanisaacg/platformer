#include "editor.h"

Editor::Editor(Level &level, Mouse &mouse, Keyboard &keyboard) : level(level), mouse(mouse), 
	keyboard(keyboard) {
	state = EditorState::Block;
}

void Editor::update() {
	mouse.update();
	switch(state) {
	case EditorState::Block:
		if(mouse.left) {
			level.place_tile(Vector2(mouse.x, mouse.y));
		} else if(mouse.right) {
			level.remove_tile(Vector2(mouse.x, mouse.y));
		}
		break;
	}
}