#include "systems/RespawnSystem.h"

#include "PhysicsConfig.h"

void RespawnSystem::update(Player& player, LevelManager& levelManager) const {
  if (player.y < FALL_THRESHOLD) {
    player.takeDamage();
    if (player.health <= 0) {
      player.health = Player::MAX_HEALTH;
      levelManager.resetToFirst(player);
    }
  }
}