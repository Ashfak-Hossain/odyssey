#include "systems/Camera.h"

#include <algorithm>

#include "Config.h"
#include "utils/Platform.h"

/**
 * @brief Construct a new Camera:: Camera object
 * - Initialize the camera position at (0, 0)
 */
Camera::Camera() : x(0), y(0) {
}

// -------------- update --------------
void Camera::update(float playerX, float worldWidth) {
  float max_x = std::max(worldWidth - WINDOW_WIDTH, 0.0f);
  x           = std::clamp(playerX - CAMERA_PLAYER_OFFSET_X, 0.0f, max_x);
  y           = 0;
}

/**
 * @brief apply the camera transform to the scene.
 * - This will translate the scene by (-camera.x, -camera.y) to create the camera effect.
 *
 *@note should be called before rendering the objects.
 */
void Camera::applyTransform() const {
  glTranslatef(-x, -y, 0);
}

/**
 * @brief convert world coordinate to screen coordinate by applying the camera transform.
 *
 * @param worldX the x coordinate in the world space
 * @return float the x coordinate in the screen space
 */
float Camera::worldToScreenX(float worldX) const {
  return worldX - x;
}

/**
 * @brief convert world coordinate to screen coordinate by applying the camera transform.
 *
 * @param worldY the y coordinate in the world space
 * @return float the y coordinate in the screen space
 */
float Camera::worldToScreenY(float worldY) const {
  return worldY - y;
}