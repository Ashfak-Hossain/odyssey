#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "ParallaxLayer.h"
#include "Tile.h"

/**
 * @brief This class will hold all static data in a level.
 * This includes the tiles, world dimensions, name;
 */
class Level {
 public:
  float                      worldWidth;
  std::string                name;
  std::vector<Tile>          tiles;
  std::vector<ParallaxLayer> bgLayers;

  Level();

  void loadTest();

  /**
   * @brief render solid objects.
   *
   * @note This should be called after camera transform
   */
  void render() const;

  /**
   * @brief build the background of the level.
   */
  void buildBackground();

  /**
   * @brief render the background layer of the level.
   * @param cameraX The horizontal position of the camera.
   *
   * @note This should be called before camera transform.
   */
  void renderBackground(float cameraX) const;
};

#endif  // LEVEL_H