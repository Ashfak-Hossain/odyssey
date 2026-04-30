#ifndef BACKGROUND_RENDERER_H
#define BACKGROUND_RENDERER_H

#include <vector>

#include "render/Renderer.h"
#include "world/ParallaxLayer.h"

/**
 * @brief Draws parallax background layers.
 * Must be called BEFORE camera transform is applied — each layer
 * manages its own partial scroll transform internally.
 */
class BackgroundRenderer {
 public:
  /**
   * @brief Draw
   *
   * @param layers Parallax Layers list
   * @param cameraX camera position for translate
   * @param renderer renderer method
   */
  void draw(const std::vector<ParallaxLayer>& layers,
            float                             cameraX,
            const Renderer&                   renderer) const;
};

#endif  // BACKGROUND_RENDERER_H