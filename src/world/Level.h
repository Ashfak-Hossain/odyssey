#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "entities/Key.h"
#include "entities/Tile.h"
#include "world/ParallaxLayer.h"

/**
 * @brief This class will hold all static data in a level.
 * This includes the tiles, world dimensions, name, bg layers, spawn point, exit door.
 * Loading and background construction are handled by LevelLoader.
 */
class Level {
 public:
  std::vector<Tile>          tiles;     // array of Tile in the level
  std::vector<Key>           keys;      // collectible keys in the level
  std::vector<ParallaxLayer> bgLayers;  // bg layers of this level

  std::string name;
  float       worldWidth;

  float playerStartX;
  float playerStartY;

  Rect exitDoor;
  bool hasExit;

  Level();
};

#endif  // LEVEL_H