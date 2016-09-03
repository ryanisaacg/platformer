//-*-C++-*-
#pragma once

#include <string>
#include <vector>

#include "state.h"

class LevelData {
public:
	LevelData(int width, int height, int square_size);
	LevelData(std::string filename, int width, int height, int square_size);
	char& operator[](const Vector2 point);
	void save(const std::string filename) const;
	void load(const std::string filename);
private:
	std::vector<char> data;
	const int width, height, square_size;
};

struct Level {
	Level(int width, int height);
	Level(std::string filename, int width, int height);
	void place_tile(const Vector2 point, SDL_Texture *texture);
	LevelData data;
	State state;
};
