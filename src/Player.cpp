#include "Player.h"

#include "Platform.h"

Player::Player()
    : x(100),
      y(GROUND_SURFACE_Y),
      vx(0),
      vy(0),
      width(PLAYER_WIDTH),
      height(PLAYER_HEIGHT),
      onGround(true) {
}

void Player::applyGravity(float deltaTime) {
  vy += GRAVITY * deltaTime;  // opengl default coord is downward.
}

Rect Player::getRect() const {
  // x, y = bottom-left corner
  return {x, y, width, height};
}

void Player::render() {
  glColor3f(1.0f, 0.3f, 0.1f);
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();
}

void Player::jump() {
  if (onGround) {
    vy       = JUMP_FORCE;
    onGround = false;
  }
}

void Player::moveLeft() {
  vx = -MOVE_SPEED;
}

void Player::moveRight() {
  vx = MOVE_SPEED;
}

void Player::stopMoving() {
  vx = 0;
}