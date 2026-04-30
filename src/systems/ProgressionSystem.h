#ifndef PROGRESSION_SYSTEM_H
#define PROGRESSION_SYSTEM_H

#include "entities/Player.h"
#include "world/LevelManager.h"

/**
 * @brief Tracks the player + level state and signals when a level transition should begin.
 *
 * @return true from update() when the player has reached the exit with the key.
 * Game::update() passes that signal to TransitionSystem::startFade().
 * This system does NOT call startFade() itself — this keeps systems decoupled.
 */
class ProgressionSystem {
 public:
  /**
   * @return true if a fade-out transition should be triggered this frame.
   */
  bool update(const Player& player, const LevelManager& levelManager) const;
};

#endif  // PROGRESSION_SYSTEM_H