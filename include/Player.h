#ifndef PLAYER_H
#define PLAYER_H

#include "Rect.h"

class Player {
 public:
  Player();

  float x, y;           // bottom left corner of the player bounding box
  float vx, vy;         // velocity in pixel/sec
  float height, width;  // size of the player bounding box
  bool  onGround;

  // returns the bounding box of the player
  Rect getRect() const;

  /**
   * @brief handle gravity of the player.
   * Game::update() will call this in every frame to apply gravity to the player.
   * @param deltaTime time elapsed since last frame(in seconds)
   */
  void applyGravity(float deltaTime);
  void render();
  void jump();
  void moveLeft();
  void moveRight();
  void stopMoving();
};

#endif