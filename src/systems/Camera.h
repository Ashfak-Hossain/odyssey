#ifndef CAMERA_H
#define CAMERA_H

/**
 * @brief This Class represents the camera in the game. The camera showed a part of the world of the
 * game. Like if the camera.x = 100 and the window width is 800 then the window show the world form
 * 100 to 900. The camera moves with the player within world range.
 */
class Camera {
 public:
  float x, y;

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

  void applyTransform() const;

  float worldToScreenX(float worldX) const;
  float worldToScreenY(float worldY) const;
};

#endif  // CAMERA_H