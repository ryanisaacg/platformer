//-*-C++-*-
#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <vector>

#include "optional.h"
#include "tilemap.h"

#include "entity.h"

void update(const TileMap<Optional<Entity>> &map, std::vector<Entity> &entities);
bool supported(const TileMap<Optional<Entity>> &map, const Entity &test);
#endif
