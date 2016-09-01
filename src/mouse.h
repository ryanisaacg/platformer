#pragma once

struct Mouse {
	Mouse();
	void update();
	bool left, middle, right, x1, x2;
	int x, y;
};