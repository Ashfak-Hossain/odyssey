#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "entities/Key.h"
#include "entities/Tile.h"
#include "world/ParallaxLayer.h"

/**
 * @brief This class will hold all static data in a level.
 * This includes the tiles, world dimensions, name;
 */
class Level {
 public:
  std::vector<Tile>          tiles;     // array of Tile in the level
  std::vector<Key>           keys;      // collectible keys in the level
  std::vector<ParallaxLayer> bgLayers;  // bg layers of this level

  std::string name;        // name of this level
  float       worldWidth;  // total world width of the level

  // ---- Player initial/spawn position in the level;
  float playerStartX;
  float playerStartY;

  Rect exitDoor;  // overlap with exitDoor will advance to the next level
  bool hasExit;

  /**
   * @brief Construct a new Level object
   */
  Level();

  /**
   * @brief load level data from txt file
   *
   * @param levelFilePath dir path of the level data file
   * @return `true` if loads level data successfully
   * @return `false` if faces any load level data error
   */
  bool load(const std::string& levelFilePath);

 private:
  /**
   * @brief build parallax background layers based on the theme.
   *
   * @param theme ocean | desert | mountain | jungle
   */
  void buildBackground(const std::string& theme);
};

#endif  // LEVEL_H