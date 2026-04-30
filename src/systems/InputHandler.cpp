#include "systems/InputHandler.h"

void InputHandler::applyMovement(Player& player, const InputManager& inputManager) const {
  if (inputManager.isHeld('a') || inputManager.isHeld('A')) {
    player.moveLeft();
  } else if (inputManager.isHeld('d') || inputManager.isHeld('D')) {
    player.moveRight();
  } else {
    player.stopMoving();
  }
}