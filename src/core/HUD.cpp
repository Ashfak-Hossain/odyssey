#include "core/HUD.h"

#include "utils/Platform.h"

HUD::HUD(const Player& player, const LevelManager& levelManager)
    : player(player), levelManager(levelManager) {
}

void HUD::render(float /*screenW*/, float screenH) const {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // --- health squares ---
  float squareSize = HUD_HEALTH_SQUARE_SIZE;
  float startX     = HUD_LEFT_PAD;
  float squareY    = screenH - HUD_TOP_PAD;

  for (int i = 0; i < Player::MAX_HEALTH; i++) {
    if (i < player.health) {
      glColor3f(HUD_HEALTH_ALIVE_R, HUD_HEALTH_ALIVE_G, HUD_HEALTH_ALIVE_B);
    } else {
      glColor3f(HUD_HEALTH_LOST_R, HUD_HEALTH_LOST_G, HUD_HEALTH_LOST_B);
    }
    float sx = startX + i * (squareSize + HUD_HEALTH_SPACING);
    glBegin(GL_QUADS);
    glVertex2f(sx, squareY);
    glVertex2f(sx + squareSize, squareY);
    glVertex2f(sx + squareSize, squareY + squareSize);
    glVertex2f(sx, squareY + squareSize);
    glEnd();
  }

  // --- key icon ---
  float keyX =
      startX + Player::MAX_HEALTH * (squareSize + HUD_HEALTH_SPACING) + HUD_KEY_ICON_X_OFFSET;
  float keyY = squareY + HUD_KEY_ICON_Y_OFFSET;

  if (player.hasKey) {
    glColor3f(HUD_KEY_ACTIVE_R, HUD_KEY_ACTIVE_G, HUD_KEY_ACTIVE_B);
  } else {
    glColor3f(HUD_KEY_INACTIVE_R, HUD_KEY_INACTIVE_G, HUD_KEY_INACTIVE_B);
  }
  glBegin(GL_QUADS);
  glVertex2f(keyX, keyY);
  glVertex2f(keyX + HUD_KEY_ICON_SIZE, keyY);
  glVertex2f(keyX + HUD_KEY_ICON_SIZE, keyY + HUD_KEY_ICON_SIZE);
  glVertex2f(keyX, keyY + HUD_KEY_ICON_SIZE);
  glEnd();

  // --- level name text ---
  float textY = squareY - HUD_TEXT_Y_OFFSET;
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos2f(startX, textY);

  const std::string& lvlName = levelManager.currentLevel().name;
  for (char c : lvlName) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }

  glPopMatrix();
}