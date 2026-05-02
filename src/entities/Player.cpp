#include "entities/Player.h"

#include "Config.h"
#include "PhysicsConfig.h"
#include "world/LevelManager.h"

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
  // x, y = bottom-left corner
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
  Rect playerRect = getRect();
  for (auto& key : keys) {
    if (!key.collected && playerRect.overlaps(key.getRect())) {
      key.collected = true;
      hasKey        = true;
    }
  }
}

void Player::checkFall(LevelManager& levelManager) {
  if (y < FALL_THRESHOLD) {
    takeDamage();
    if (health <= 0) {
      health = MAX_HEALTH;
      levelManager.resetToFirst(*this);
    }
  }
}