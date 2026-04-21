#ifndef PLAYER_H
#define PLAYER_H

class Player {
 public:
  Player();

  float x, y;    // player position
  float vx, vy;  // velocity
  float height, width;
  bool  onGround;

  void update(float deltaTime);
  void render();
  void jump();
  void moveLeft();
  void moveRight();
  void stopMoving();
};

#endif