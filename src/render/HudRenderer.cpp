#include "render/HudRenderer.h"

#include "ColorPalette.h"
#include "HudConfig.h"

void HudRenderer::draw(const Player&       player,
                       const LevelManager& levelManager,
                       float /*screenW*/,
                       float           screenH,
                       const Renderer& renderer) const {
  renderer.pushMatrix();
  renderer.loadIdentity();

  float squareSize = HUD_HEALTH_SQUARE_SIZE;
  float startX     = HUD_LEFT_PAD;
  float squareY    = screenH - HUD_TOP_PAD;

  // --- health squares ---
  for (int i = 0; i < Player::MAX_HEALTH; i++) {
    float sx = startX + i * (squareSize + HUD_HEALTH_SPACING);
    if (i < player.health) {
      renderer.drawQuad(sx,
                        squareY,
                        squareSize,
                        squareSize,
                        HUD_HEALTH_ALIVE_R,
                        HUD_HEALTH_ALIVE_G,
                        HUD_HEALTH_ALIVE_B);
    } else {
      renderer.drawQuad(sx,
                        squareY,
                        squareSize,
                        squareSize,
                        HUD_HEALTH_LOST_R,
                        HUD_HEALTH_LOST_G,
                        HUD_HEALTH_LOST_B);
    }
  }

  // --- key icon ---
  float keyX =
      startX + Player::MAX_HEALTH * (squareSize + HUD_HEALTH_SPACING) + HUD_KEY_ICON_X_OFFSET;
  float keyY = squareY + HUD_KEY_ICON_Y_OFFSET;

  if (player.hasKey) {
    renderer.drawQuad(keyX,
                      keyY,
                      HUD_KEY_ICON_SIZE,
                      HUD_KEY_ICON_SIZE,
                      HUD_KEY_ACTIVE_R,
                      HUD_KEY_ACTIVE_G,
                      HUD_KEY_ACTIVE_B);
  } else {
    renderer.drawQuad(keyX,
                      keyY,
                      HUD_KEY_ICON_SIZE,
                      HUD_KEY_ICON_SIZE,
                      HUD_KEY_INACTIVE_R,
                      HUD_KEY_INACTIVE_G,
                      HUD_KEY_INACTIVE_B);
  }

  // --- level name text ---
  float textY = squareY - HUD_TEXT_Y_OFFSET;
  renderer.drawText(startX, textY, levelManager.currentLevel().name, 1.0f, 1.0f, 1.0f);

  renderer.popMatrix();
}