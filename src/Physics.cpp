#include "Physics.h"

#include "Config.h"
#include "Rect.h"

void Physics::update(Player& player, const std::vector<Tile>& tiles, float deltaTime) {
  // applied gravity to player.
  player.applyGravity(deltaTime);

  // ------ X axis movement and collision ------
  // move x axis only
  player.x += player.vx * deltaTime;

  // edges of world
  if (player.x < 0) {
    player.x  = 0;
    player.vx = 0;
  }

  // resolve x-axis collision with tiles
  for (auto& tile : tiles) {
    resolveX(player, tile);
  }

  // ------ Y axis movement and collision ------
  // move y axis only
  player.y += player.vy * deltaTime;

  player.onGround = false;  // reset ground before collision check

  // resolve y-axis collision with tiles
  for (auto& tile : tiles) {
    resolveY(player, tile);
  }
}

/**
 * @brief Resolve collision on the X-axis.
 *
 * @param tile The tile to check collision with.
 */
void Physics::resolveX(Player& player, const Tile& tile) {
  Rect playerRect = player.getRect();
  Rect tileRect   = tile.getRect();

  // no collision, do nothing
  if (!playerRect.overlaps(tileRect)) {
    return;
  }

  float overlapX = playerRect.overlapX(tileRect);

  // by measure center of player and tile. we can get which direction player comes from and push the
  // player to the direction.
  if (playerRect.centerX() < tileRect.centerX()) {
    player.x -= overlapX;
  } else {
    player.x += overlapX;
  }

  player.vx = 0;
}

/**
 * @brief Resolve collision on the Y-axis.
 *
 * @param tile The tile to check collision with.
 */
void Physics::resolveY(Player& player, const Tile& tile) {
  Rect playerRect = player.getRect();
  Rect tileRect   = tile.getRect();

  // no collision, do nothing
  if (!playerRect.overlaps(tileRect)) {
    return;
  }

  float overlapY = playerRect.overlapY(tileRect);
  if (playerRect.centerY() > tileRect.centerY()) {
    player.y += overlapY;
    player.vy       = 0;
    player.onGround = true;
  } else {
    player.y -= overlapY;
    player.vy = 0;
  }
}