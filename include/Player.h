#ifndef PLAYER_H
#define PLAYER_H

class Player {
 public:
  Player();

  float x, y;           // bottom left corner of the player bounding box
  float vx, vy;         // velocity in pixel/sec
  float height, width;  // size of the player bounding box
  bool  onGround;

  void update(float deltaTime);
  void render();
  void jump();
  void moveLeft();
  void moveRight();
  void stopMoving();
};

#endif