#ifndef PARALLAXLAYER_H
#define PARALLAXLAYER_H

#include <vector>

/**
 * @brief layer for sky gradient.
 * - Full-width color stripe [0 - WORLD_WIDTH]
 */
struct ColorBand {
  float yBottom, yTop;
  float r, g, b;
};

/**
 * @brief  triangle in world-space coordinates.
 * - Used for hills
 */
struct Triangle {
  float x1, y1;
  float x2, y2;
  float x3, y3;
  float r, g, b;
};

class ParallaxLayer {
 public:
  /**
   * @brief Camera-speeding factor in [0.0, 1.0].
   *   0.0 → static
   *   0.2 → slow
   *   0.5 → faster
   *   1.0 → moves the camera (foreground)
   */
  float                  scrollFactor;
  std::vector<ColorBand> bands;   // horizontal color fills
  std::vector<Triangle>  shapes;  // decorative geometry

  // Constructs an empty layer.
  ParallaxLayer(float factor);
};

#endif  // PARALLAXLAYER_H