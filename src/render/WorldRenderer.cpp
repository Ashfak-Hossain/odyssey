#include "render/WorldRenderer.h"

#include "ColorPalette.h"

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

// =================== Draw Keys ===================
void WorldRenderer::drawKeys(const std::vector<Key>& keys, const Renderer& renderer) const {
  for (const auto& k : keys) {
    if (k.collected)
      continue;
    renderer.drawQuad(
        k.x, k.y, k.width, k.height, HUD_KEY_ACTIVE_R, HUD_KEY_ACTIVE_G, HUD_KEY_ACTIVE_B);
    renderer.drawQuadOutline(k.x, k.y, k.width, k.height, 0.7f, 0.55f, 0.0f);
  }
}

// =================== Key Exit Door ===================
void WorldRenderer::drawExit(const Rect& door, bool locked, const Renderer& renderer) const {
  if (locked) {
    renderer.drawQuad(door.x,
                      door.y,
                      door.width,
                      door.height,
                      EXIT_LOCKED_FILL_R,
                      EXIT_LOCKED_FILL_G,
                      EXIT_LOCKED_FILL_B);
    renderer.drawQuadOutline(door.x,
                             door.y,
                             door.width,
                             door.height,
                             EXIT_LOCKED_BORDER_R,
                             EXIT_LOCKED_BORDER_G,
                             EXIT_LOCKED_BORDER_B,
                             EXIT_BORDER_LINE_WIDTH);
  } else {
    renderer.drawQuad(door.x,
                      door.y,
                      door.width,
                      door.height,
                      EXIT_UNLOCKED_FILL_R,
                      EXIT_UNLOCKED_FILL_G,
                      EXIT_UNLOCKED_FILL_B);
    renderer.drawQuadOutline(door.x,
                             door.y,
                             door.width,
                             door.height,
                             EXIT_UNLOCKED_BORDER_R,
                             EXIT_UNLOCKED_BORDER_G,
                             EXIT_UNLOCKED_BORDER_B,
                             EXIT_BORDER_LINE_WIDTH);
  }
}