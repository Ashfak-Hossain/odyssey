#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "Config.h"
#include "entities/Key.h"
#include "entities/Tile.h"
#include "world/ParallaxLayer.h"

/**
 * @brief Static data for a single level.
 */
struct Level {
  std::vector<Tile>          tiles;
  std::vector<Key>           keys;
  std::vector<ParallaxLayer> bgLayers;

  std::string name;
  float       worldWidth   = WORLD_WIDTH;
  float       playerStartX = 100.0f;
  float       playerStartY = GROUND_SURFACE_Y;
  Rect        exitDoor     = {0, 0, 0, 0};
  bool        hasExit      = false;
};

#endif  // LEVEL_H