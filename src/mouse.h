#pragma once

struct Mouse {
	Mouse();
	Mouse(float xscale, float yscale);
	void update();
	bool left, middle, right, x1, x2;
	int x, y;
	const float xscale, yscale;
};
