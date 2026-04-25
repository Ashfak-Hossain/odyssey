#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "Tile.h"

/**
 * @brief This class will hold all static data in a level.
 * This includes the tiles, world dimensions, name;
 */
class Level {
 public:
  std::vector<Tile> tiles;
  float             worldWidth;
  std::string       name;

  Level();

  void loadTest();
  void render() const;
};

#endif  // LEVEL_H