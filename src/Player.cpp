#include "Player.h"

#include "Platform.h"

Player::Player()
    : x(100),
      y(GROUND_Y),
      vx(0),
      vy(0),
      width(PLAYER_WIDTH),
      height(PLAYER_HEIGHT),
      onGround(true) {
}

/**
 * @brief Updates the player's position and velocity based on the elapsed time and gravity at
 * each frame.
 * @param deltaTime Time elapsed since the last update, in seconds.
 *
 * @note The player's vertical velocity is affected by gravity. Position is updated by current
 * velocity. If the player collides with the ground, position is reset to ground, vertical velocity
 * is set to 0, and the ground flag is on;
 */
void Player::update(float deltaTime) {
  vy += GRAVITY * deltaTime;  // opengl default coord is downward.

  // Update position based on velocity and deltaTime (velocity in pixel/sec * time in sec = distance
  // in pixel)
  x += vx * deltaTime;
  y += vy * deltaTime;

  // Collision with the ground
  if (y <= GROUND_Y) {
    y        = GROUND_Y;
    vy       = 0;
    onGround = true;
  } else {
    onGround = false;
  }
}

void Player::render() {
  glColor3f(1, 0, 0);
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