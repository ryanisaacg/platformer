#include "level.h"

#include <ifstream>
#include <ofstream>
#include <sstream>

LevelData::LevelData(int width, int height, int square_size) : width(width), height(height), square_size(square_size), data() {}
LevelData::LevelData(std::string filename, int width, int height, int square_size) : LevelData(width, height, square_size) {
	load(filename);
}

char& LevelData::operator[](Vector2 point) {
	int x = (int)point.x / square_size;
	int y = (int)point.y / square_size;
	return data[y * width + x];
}

void LevelData::save(const std::string filename) const {
	std::ofstream ofs(filename, std::ofstream::out);
	for(int i = 0; i < data.size(); i++)
		ofs << data[i];
	ofs.close();
}

void LevelData::load(const std::string filename) {
	std::ifstream t(filename);
	std::stringstream buffer;
	buffer << t.rdbuf();
	auto str = buffer.str();
	int length = str.length();
	data = std::vector(length);
	for(int i = 0; i < length; i++)
		data[i] = str.char_at(i);
}
