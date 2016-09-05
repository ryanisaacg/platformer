//-*-C++-*-
#pragma once

#include <string>
#include <vector>

#include "SDL.h"

#include "state.h"
#include "window.h"

class LevelData {
public:
	LevelData(int width, int height, int square_size);
	LevelData(std::string filename, int width, int height, int square_size);
	char& operator[](const Vector2 point);
	void save(const std::string filename) const;
	void load(const std::string filename);
private:
	void expand_to_capacity();
	std::vector<char> data;
	const int width, height, square_size;
};

struct Level {
public:
	Level(int width, int height, Window &window);
	Level(std::string filename, int width, int height, Window &window);
	void place_tile(const Vector2 point);
	void remove_tile(const Vector2 point);
	void restart();
	LevelData data;
	State state;
	static const int TILE_SIZE = 32;
private:
	SDL_Texture *wall;
	int width, height;
};
