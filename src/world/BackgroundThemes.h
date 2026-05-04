#ifndef BACKGROUND_THEMES_H
#define BACKGROUND_THEMES_H

#include <vector>

#include "world/ParallaxLayer.h"

/**
 * @brief Builds parallax background layers for bg theme
 *   0 → ocean, 1 → desert, 2 → mountain
 *
 * Each theme generate 3 layers:
 *   - sky    (static)   : 2-colour gradient bands
 *   - mid    (slow)     : distant triangles
 *   - near   (faster)   : close triangles
 */
class BackgroundThemes {
 public:
  static void build(int levelIndex, std::vector<ParallaxLayer>& layers);

 private:
  static void buildOcean(std::vector<ParallaxLayer>& layers);
  static void buildDesert(std::vector<ParallaxLayer>& layers);
  static void buildMountain(std::vector<ParallaxLayer>& layers);
};

#endif  // BACKGROUND_THEMES_H
