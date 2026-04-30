#ifndef RESPAWN_SYSTEM_H
#define RESPAWN_SYSTEM_H

#include "entities/Player.h"
#include "world/LevelManager.h"

/**
 * @brief Handles fall-off damage and game-over reset.
 *
 * Each frame: if player falls below FALL_THRESHOLD, call takeDamage().
 * If health reaches zero, restore full health and reset to level 1.
 */
class RespawnSystem {
 public:
  void update(Player& player, LevelManager& levelManager) const;
};

#endif  // RESPAWN_SYSTEM_H