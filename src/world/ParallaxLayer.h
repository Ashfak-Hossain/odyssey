#ifndef PARALLAXLAYER_H
#define PARALLAXLAYER_H

#include <vector>

struct ColorBand {
  float yBottom, yTop;
  float r, g, b;  // color
};

struct Triangle {
  float x1, y1;
  float x2, y2;
  float x3, y3;
  float r, g, b;  // color
};

class ParallaxLayer {
 public:
  float                  scrollFactor;
  std::vector<ColorBand> bands;   // horizontal color fills
  std::vector<Triangle>  shapes;  // decorative geometry

  ParallaxLayer(float factor);

  /**
   * @brief Renders the parallax layer based on the camera's horizontal position.
   * @param cameraX The horizontal position of the camera.
   */
  void render(float cameraX) const;
};

#endif  // PARALLAXLAYER_H