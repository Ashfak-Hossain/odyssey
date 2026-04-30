#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "entities/Player.h"
#include "systems/InputManager.h"

/**
 * @brief Translates raw InputManager key state into player movement intents.
 * Keeps key-to-action mapping in one place so Game::update() stays clean.
 */
class InputHandler {
 public:
  /**
   * @brief Reads held keys and calls the appropriate Player movement method.
   * A/left held  → player.moveLeft()
   * D/right held → player.moveRight()
   * neither      → player.stopMoving()
   */
  void applyMovement(Player& player, const InputManager& inputManager) const;
};

#endif  // INPUT_HANDLER_H