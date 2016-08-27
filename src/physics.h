#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <vector>

#include "optional.h"
#include "tilemap.h"

#include "entity.h"

void update(TileMap<Optional<Entity>> map, std::vector<Entity> &entities);
#endif
