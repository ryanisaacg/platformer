#pragma once

#include "keyboard.h"
#include "level.h"
#include "mouse.h"

class Editor {
public:
	Editor(Level &level, Mouse &mouse, Keyboard &keyboard);
	void update();
private:
	Level &level;
	Mouse &mouse;
	Keyboard &keyboard;
};