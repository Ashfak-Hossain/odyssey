#ifndef TRANSITION_RENDERER_H
#define TRANSITION_RENDERER_H

#include "render/Renderer.h"

/**
 * @brief Draws the full-screen black fade overlay.
 * alpha = 0 is invisible, 1 is fully black.
 * Must be called last in the render pipeline (on top of everything).
 */
class TransitionRenderer {
 public:
  void draw(float alpha, float screenW, float screenH, const Renderer& renderer) const;
};

#endif  // TRANSITION_RENDERER_H