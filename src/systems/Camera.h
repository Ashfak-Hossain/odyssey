#ifndef CAMERA_H
#define CAMERA_H

/**
 * @brief This Class represents the camera in the game. Visible range of the world.
 * If camera.x = 100 and window width is 800, the visible world range is [100, 900].
 * Camera tracks the player within world bounds.
 */
class Camera {
 public:
  float x, y;  // bottom-left corner of the camera

  Camera();

  /**
   * @brief update the camera position based on the player position.
   * - The camera will keep the player at the `CAMERA_PLAYER_OFFSET_X` from the left of the screen.
   * - max-x = max coords of camera in x.
   * - clamps the camera-x in between [0, max-x]
   *
   * @param playerX x position of the player
   * @param worldWidth width of the world
   */
  void update(float playerX, float worldWidth);

  /**
   * @brief apply the camera transform to the scene.
   * - This will translate the scene by (-camera.x, -camera.y) to create the camera effect.
   *
   *@note should be called before rendering the objects.
   */
  void applyTransform() const;

  /**
   * @brief convert world coordinate to screen coordinate
   *
   * @param worldX the x coordinate in the world space
   * @return float the x coordinate in the screen space
   */
  float worldToScreenX(float worldX) const;

  /**
   * @brief convert world coordinate to screen coordinate
   *
   * @param worldY the y coordinate in the world space
   * @return float the y coordinate in the screen space
   */
  float worldToScreenY(float worldY) const;
};

#endif  // CAMERA_H