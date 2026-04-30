#include "render/TransitionRenderer.h"

void TransitionRenderer::draw(float           alpha,
                              float           screenW,
                              float           screenH,
                              const Renderer& renderer) const {
  if (alpha <= 0.0f) {
    return;  // skip if fully transparent
  }

  renderer.pushMatrix();
  renderer.loadIdentity();
  renderer.enableBlending();
  renderer.drawQuadAlpha(0.0f, 0.0f, screenW, screenH, 0.0f, 0.0f, 0.0f, alpha);
  renderer.disableBlending();
  renderer.popMatrix();
}