#include "render/WorldRenderer.h"

#include <cmath>

#include "ColorPalette.h"
#include "utils/Platform.h"

// =================== Key Tiles ===================
void WorldRenderer::drawTiles(const std::vector<Tile>& tiles, const Renderer& renderer) const {
  for (const auto& t : tiles) {
    renderer.drawQuad(t.x, t.y, t.width, t.height, t.r, t.g, t.b);
    renderer.drawQuadOutline(t.x,
                             t.y,
                             t.width,
                             t.height,
                             t.r * TILE_BORDER_DARKNESS,
                             t.g * TILE_BORDER_DARKNESS,
                             t.b * TILE_BORDER_DARKNESS);
  }
}

void WorldRenderer::drawKeyFace(float r,
                                float g,
                                float b,
                                float x0,
                                float y0,
                                float z0,
                                float x1,
                                float y1,
                                float z1,
                                float x2,
                                float y2,
                                float z2,
                                float x3,
                                float y3,
                                float z3) {
  glColor3f(r, g, b);
  glBegin(GL_QUADS);
  glVertex3f(x0, y0, z0);
  glVertex3f(x1, y1, z1);
  glVertex3f(x2, y2, z2);
  glVertex3f(x3, y3, z3);
  glEnd();
}

void WorldRenderer::drawKeyFaceOutline(float x0,
                                       float y0,
                                       float z0,
                                       float x1,
                                       float y1,
                                       float z1,
                                       float x2,
                                       float y2,
                                       float z2,
                                       float x3,
                                       float y3,
                                       float z3) {
  glBegin(GL_LINE_LOOP);
  glVertex3f(x0, y0, z0);
  glVertex3f(x1, y1, z1);
  glVertex3f(x2, y2, z2);
  glVertex3f(x3, y3, z3);
  glEnd();
}

void WorldRenderer::drawKeyBox(float hw, float hh, float hd) {
  drawKeyFace(HUD_KEY_ACTIVE_R,
              HUD_KEY_ACTIVE_G,
              HUD_KEY_ACTIVE_B,
              -hw,
              -hh,
              hd,
              hw,
              -hh,
              hd,
              hw,
              hh,
              hd,
              -hw,
              hh,
              hd);  // Front
  drawKeyFace(HUD_KEY_ACTIVE_R * 0.5f,
              HUD_KEY_ACTIVE_G * 0.5f,
              0.0f,
              hw,
              -hh,
              -hd,
              -hw,
              -hh,
              -hd,
              -hw,
              hh,
              -hd,
              hw,
              hh,
              -hd);  // Back
  drawKeyFace(HUD_KEY_ACTIVE_R * 0.75f,
              HUD_KEY_ACTIVE_G * 0.75f,
              0.0f,
              hw,
              -hh,
              -hd,
              hw,
              -hh,
              hd,
              hw,
              hh,
              hd,
              hw,
              hh,
              -hd);  // Right
  drawKeyFace(HUD_KEY_ACTIVE_R * 0.75f,
              HUD_KEY_ACTIVE_G * 0.75f,
              0.0f,
              -hw,
              -hh,
              hd,
              -hw,
              -hh,
              -hd,
              -hw,
              hh,
              -hd,
              -hw,
              hh,
              hd);  // Left
  drawKeyFace(HUD_KEY_ACTIVE_R,
              HUD_KEY_ACTIVE_G,
              0.35f,
              -hw,
              hh,
              hd,
              hw,
              hh,
              hd,
              hw,
              hh,
              -hd,
              -hw,
              hh,
              -hd);  // Top
  drawKeyFace(HUD_KEY_ACTIVE_R * 0.45f,
              HUD_KEY_ACTIVE_G * 0.45f,
              0.0f,
              -hw,
              -hh,
              -hd,
              hw,
              -hh,
              -hd,
              hw,
              -hh,
              hd,
              -hw,
              -hh,
              hd);  // Bottom

  glColor3f(0.7f, 0.55f, 0.0f);
  glLineWidth(1.5f);
  drawKeyFaceOutline(-hw, -hh, hd, hw, -hh, hd, hw, hh, hd, -hw, hh, hd);      // Front
  drawKeyFaceOutline(hw, -hh, -hd, -hw, -hh, -hd, -hw, hh, -hd, hw, hh, -hd);  // Back
  drawKeyFaceOutline(hw, -hh, -hd, hw, -hh, hd, hw, hh, hd, hw, hh, -hd);      // Right
  drawKeyFaceOutline(-hw, -hh, hd, -hw, -hh, -hd, -hw, hh, -hd, -hw, hh, hd);  // Left
  drawKeyFaceOutline(-hw, hh, hd, hw, hh, hd, hw, hh, -hd, -hw, hh, -hd);      // Top
  drawKeyFaceOutline(-hw, -hh, -hd, hw, -hh, -hd, hw, -hh, hd, -hw, -hh, hd);  // Bottom
}

// =================== Draw Keys ===================
void WorldRenderer::drawKeys(const std::vector<Key>& keys,
                             const Renderer&         renderer,
                             float                   deltaTime) {
  keyAngle += 90.0f * deltaTime;
  if (keyAngle >= 360.0f) {
    keyAngle -= 360.0f;
  }

  for (const auto& k : keys) {
    if (k.collected) {
      continue;
    }

    renderer.pushMatrix();
    renderer.translate(k.x + k.width * 0.5f, k.y + k.height * 0.5f, 0.0f);
    renderer.rotate(keyAngle, 1.0f, 1.0f, 1.0f);
    drawKeyBox(k.width * 0.5f, k.height * 0.5f, k.width * 0.5f);
    renderer.popMatrix();
  }
}

// =================== Key Exit Door ===================
void WorldRenderer::drawExit(const Rect& door, bool locked, const Renderer& renderer) const {
  float r = locked ? 0.50f : 0.05f;
  float g = locked ? 0.05f : 0.50f;
  float b = locked ? 0.05f : 0.05f;

  int xLeft   = door.x;
  int yTop    = door.y;
  int xRight  = door.x + door.width;
  int yBottom = door.y + door.height;

  renderer.drawMidpointLine(xLeft, yTop, xRight, yTop, r, g, b);        // Top
  renderer.drawMidpointLine(xLeft, yBottom, xRight, yBottom, r, g, b);  // Bottom
  renderer.drawMidpointLine(xLeft, yTop, xLeft, yBottom, r, g, b);      // Left
  renderer.drawMidpointLine(xRight, yTop, xRight, yBottom, r, g, b);    // Right

  renderer.drawMidpointLine(xLeft, yTop, xRight, yBottom, r, g, b);  // Top-Left to Bottom-Right
  renderer.drawMidpointLine(xRight, yTop, xLeft, yBottom, r, g, b);  // Top-Right to Bottom-Left
}