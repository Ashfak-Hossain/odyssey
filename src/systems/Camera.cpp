#include "systems/Camera.h"

#include <algorithm>

#include "Config.h"
#include "utils/Platform.h"

Camera::Camera() : x(0), y(0) {
}

// -------------- update --------------
void Camera::update(float playerX, float worldWidth) {
  float max_x = std::max(worldWidth - WINDOW_WIDTH, 0.0f);
  x           = std::clamp(playerX - CAMERA_PLAYER_OFFSET_X, 0.0f, max_x);
  y           = 0;
}

// -------------- translate --------------
void Camera::applyTransform() const {
  glTranslatef(-x, -y, 0);
}

// -------------- world to screen X --------------
float Camera::worldToScreenX(float worldX) const {
  return worldX - x;
}

// -------------- world to screen Y --------------
float Camera::worldToScreenY(float worldY) const {
  return worldY - y;
}