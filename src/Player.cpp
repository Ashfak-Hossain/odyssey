#include "Player.h"

#include "Platform.h"

Player::Player() : x(100), y(0), vx(0), vy(0), width(20), height(40), onGround(true) {
}

void Player::update(float deltaTime) {
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
}

void Player::moveLeft() {
}

void Player::moveRight() {
}

void Player::stopMoving() {
}