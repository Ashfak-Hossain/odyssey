#include "entities/Player.h"

#include "Config.h"
#include "PhysicsConfig.h"

Player::Player()
    : x(PLAYER_DEFAULT_START_X),
      y(GROUND_SURFACE_Y),
      vx(0),
      vy(0),
      width(PLAYER_WIDTH),
      height(PLAYER_HEIGHT),
      onGround(true),
      startX(PLAYER_DEFAULT_START_X),
      startY(GROUND_SURFACE_Y) {
}

void Player::applyGravity(float deltaTime) {
  vy += GRAVITY * deltaTime;  // opengl default coord is downward.
}

Rect Player::getRect() const {
  return {x, y, width, height};
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

void Player::respawn() {
  x        = startX;
  y        = startY;
  vx       = 0;
  vy       = 0;
  onGround = false;
}

void Player::takeDamage() {
  health--;
  hasKey = false;
  respawn();
}

void Player::applyInput(const InputManager& inputManager) {
  if (inputManager.isHeld('a') || inputManager.isHeld('A')) {
    moveLeft();
  } else if (inputManager.isHeld('d') || inputManager.isHeld('D')) {
    moveRight();
  } else {
    stopMoving();
  }
}

void Player::collectKeys(std::vector<Key>& keys) {
  Rect playerRect   = getRect();
  bool allCollected = true;
  for (auto& key : keys) {
    if (!key.collected && playerRect.overlaps(key.getRect())) {
      key.collected = true;
    }
    if (!key.collected) {
      allCollected = false;
    }
  }
  hasKey = allCollected;
}

bool Player::checkFall() {
  if (y < FALL_THRESHOLD) {
    takeDamage();
    return true;
  }
  return false;
}