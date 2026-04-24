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
  void update(float playerX, float playerY);

  void applyTransform() const;

  float worldToScreenX(float worldX) const;
  float worldToScreenY(float worldY) const;
};

#endif