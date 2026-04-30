#include "HUD.h"

#include "Platform.h"

HUD::HUD(const Player& player, const LevelManager& levelManager)
    : player(player), levelManager(levelManager) {
}

void HUD::render(float /*screenW*/, float screenH) const {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // health squares
  float squareSize = 20.0f;
  float startX     = 10.0f;
  float squareY    = screenH - 30.0f;  // 30px from top

  for (int i = 0; i < Player::MAX_HEALTH; i++) {
    if (i < player.health) {
      glColor3f(0.9f, 0.15f, 0.15f);  // red = alive
    } else {
      glColor3f(0.25f, 0.25f, 0.25f);  // dark gray = lost
    }
    float sx = startX + i * (squareSize + 8.0f);
    glBegin(GL_QUADS);
    glVertex2f(sx, squareY);
    glVertex2f(sx + squareSize, squareY);
    glVertex2f(sx + squareSize, squareY + squareSize);
    glVertex2f(sx, squareY + squareSize);
    glEnd();
  }

  // key icon (gold quad, right of health squares)
  float keyX = startX + Player::MAX_HEALTH * (squareSize + 8.0f) + 6.0f;
  float keyY = squareY + 2.0f;

  if (player.hasKey) {
    glColor3f(1.0f, 0.85f, 0.0f);
  } else {
    glColor3f(0.3f, 0.3f, 0.3f);
  }
  glBegin(GL_QUADS);
  glVertex2f(keyX, keyY);
  glVertex2f(keyX + 16.0f, keyY);
  glVertex2f(keyX + 16.0f, keyY + 16.0f);
  glVertex2f(keyX, keyY + 16.0f);
  glEnd();

  // level name text, 4px below the health row
  float textY = squareY - 18.0f;
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos2f(startX, textY);

  const std::string& lvlName = levelManager.currentLevel().name;
  for (char c : lvlName) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }

  glPopMatrix();
}
