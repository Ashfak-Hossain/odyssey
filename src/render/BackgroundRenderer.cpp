#include "render/BackgroundRenderer.h"

#include "CameraConfig.h"

void BackgroundRenderer::draw(const std::vector<ParallaxLayer>& layers,
                              float                             cameraX,
                              const Renderer&                   renderer) const {
  for (const auto& layer : layers) {
    renderer.loadIdentity();
    renderer.translate(-cameraX * layer.scrollFactor, 0.0f);

    for (const auto& band : layer.bands) {
      renderer.drawQuad(
          0, band.yBottom, WORLD_WIDTH, band.yTop - band.yBottom, band.r, band.g, band.b);
    }

    for (const auto& tri : layer.shapes) {
      renderer.drawTriangle(tri.x1, tri.y1, tri.x2, tri.y2, tri.x3, tri.y3, tri.r, tri.g, tri.b);
    }
  }
}