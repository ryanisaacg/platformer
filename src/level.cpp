#include "level.h"

#include <fstream>
#include <sstream>

LevelData::LevelData(int width, int height, int square_size) : width(width), height(height), square_size(square_size), data() {
	expand_to_capacity();
}

LevelData::LevelData(std::string filename, int width, int height, int square_size) : LevelData(width, height, square_size) {
	load(filename);
	expand_to_capacity();
}

void LevelData::expand_to_capacity() {
	auto old = data;
	data = std::vector<char>(width * height);
	for(int i = 0; i < old.size(); i++)
		data[i] = old[i];
	for(int i = old.size(); i < data.size(); i++)
		data[i] = '\0';
}

char& LevelData::operator[](Vector2 point) {
	int x = (int)point.x / square_size;
	int y = (int)point.y / square_size;
	int index = y * (width / square_size) + x;
	return data[index];
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
	data = std::vector<char>(length);
	for(int i = 0; i < length; i++)
		data[i] = str.at(i);
}


Level::Level(int width, int height, Window &window) : data(width, height, TILE_SIZE), 
	state(*this, width, height, TILE_SIZE), width(width), height(height) {
	wall = window.load_texture("../img/red.png");
}

Level::Level(std::string filename, int width, int height, Window &window) : 
	data(filename, width, height, TILE_SIZE), state(*this, width, height, TILE_SIZE), width(width), height(height) {
	wall = window.load_texture("../img/red.png");
	restart();
}

Vector2 snap(const Vector2 point, int TILE_SIZE) {
	auto snapped = point;
	snapped.x = ((int)snapped.x / TILE_SIZE) * TILE_SIZE;
	snapped.y = ((int)snapped.y / TILE_SIZE) * TILE_SIZE;
	return snapped;
}

void Level::place_tile(const Vector2 point) {
	auto snapped = snap(point, TILE_SIZE);
	state.place_tile(snapped, wall);
	data[snapped] = 'X';
}

void Level::remove_tile(const Vector2 point) {
	auto snapped = snap(point, TILE_SIZE);
	state.remove_tile(snapped);
	data[snapped] = ' ';
}

void Level::set_player_position(const Vector2 point) {
	auto snapped = snap(point, TILE_SIZE);
	for(int i = 0; i < data.data.size(); i++)
		if(data.data[i] == 'P')
			data.data[i] = ' ';
	data[snapped] = 'P';
	for(int i = 0; i < state.entities.size(); i++) {
		auto &entity = state.entities[i];
		if(entity.control == ControlType::PLAYER) {
			entity.bounds->setX(snapped.x);
			entity.bounds->setY(snapped.y);
			return;
		}
	}
	//No player found:
	auto &player = state.spawn(Rect(snapped.x, snapped.y, TILE_SIZE, TILE_SIZE), wall, false, ControlType::PLAYER);
	player.alignment = Alignment::PLAYER;
	player.gravity = 0.5f;
}

void Level::add_enemy(const Vector2 point) {
	auto snapped = snap(point, TILE_SIZE);
	auto &enemy = state.spawn(Rect(snapped.x, snapped.y, TILE_SIZE, TILE_SIZE), wall, false, ControlType::ENEMY);
	enemy.alignment = Alignment::ENEMY;
	enemy.gravity = 0.5f;
}

void Level::remove_enemy(const Vector2 point) {
	for(int i = 0; i < state.entities.size(); i++)
		if(state.entities[i].bounds->contains(point))
			state.entities[i].health = 0;
	state.cleanup();
}

void Level::restart() {
	state.entities.clear();
	for(int x = 0; x < width; x += TILE_SIZE) {
		for(int y = 0; y < height; y += TILE_SIZE) {
			auto pos = Vector2(x, y);
			char square = data[pos];
			switch(square) {
			case ' ':
				break;
			case 'X':
				state.place_tile(pos, wall);
				break;
			case 'P':
				set_player_position(pos);
				break;
			case 'E':
				add_enemy(pos);
				break;
			}
		}
	}
}
