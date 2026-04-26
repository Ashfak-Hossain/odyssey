#include "Camera.h"

#include "Config.h"
#include "Platform.h"

/**
 * @brief Construct a new Camera:: Camera object
 * - Initialize the camera position at (0, 0)
 */
Camera::Camera() : x(0), y(0) {
}

/**
 * @brief update the camera position based on the player position.
 * - The camera will keep the player at the `CAMERA_PLAYER_OFFSET_X` from the left of the screen.
 * - The camera will not go beyond the world `left` and `right` edges.
 * - The camera y is fixed at `0` because we only have horizontal movement in this game.
 *
 * @param playerX
 * @param playerY
 */
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