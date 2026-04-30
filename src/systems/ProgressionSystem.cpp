#include "systems/ProgressionSystem.h"

bool ProgressionSystem::update(const Player& player, const LevelManager& levelManager) const {
  return levelManager.shouldAdvance(player);
}