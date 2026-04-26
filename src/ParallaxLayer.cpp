#include "ParallaxLayer.h"

#include "Config.h"
#include "Platform.h"

ParallaxLayer::ParallaxLayer(float factor) : scrollFactor(factor) {
}

void ParallaxLayer::render(float cameraX) const {
  glLoadIdentity();
  // Apply current layer's partial camera transform
  glTranslatef(-cameraX * scrollFactor, 0.0f, 0.0f);

  // render color bands
  for (const auto& band : bands) {
    glColor3f(band.r, band.g, band.b);
    glBegin(GL_QUADS);

    glVertex2f(0, band.yBottom);
    glVertex2f(WORLD_WIDTH, band.yBottom);
    glVertex2f(WORLD_WIDTH, band.yTop);
    glVertex2f(0, band.yTop);

    glEnd();
  }

  // render shapes
  for (const auto& tri : shapes) {
    glColor3f(tri.r, tri.g, tri.b);
    glBegin(GL_TRIANGLES);

    glVertex2f(tri.x1, tri.y1);
    glVertex2f(tri.x2, tri.y2);
    glVertex2f(tri.x3, tri.y3);

    glEnd();
  }
}