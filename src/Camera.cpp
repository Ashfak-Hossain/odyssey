#include "Camera.h"

#include "Config.h"
#include "Platform.h"

Camera::Camera() : x(0), y(0) {
}

void Camera::update(float playerX, float playerY) {
  // the camera x is always keep the player at the camera offset
  x = playerX - CAMERA_PLAYER_OFFSET_X;

  // cant go beyond the world left edge
  if (x < 0) {
    x = 0;
  }

  // cant go beyond the world right edge
  float maxX = WORLD_WIDTH - WINDOW_WIDTH;
  if (x > maxX) {
    x = maxX;
  }

  y = 0;
}

void Camera::applyTransform() const {
  glTranslatef(-x, -y, 0);
}

float Camera::worldToScreenX(float worldX) const {
  return worldX - x;
}

float Camera::worldToScreenY(float worldY) const {
  return worldY - y;
}