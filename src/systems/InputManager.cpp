#include "systems/InputManager.h"

InputManager::InputManager() {
  for (int i = 0; i < 256; ++i) {
    keys[i] = false;
  }
}

void InputManager::keyDown(unsigned char key) {
  keys[key] = true;
}

void InputManager::keyUp(unsigned char key) {
  keys[key] = false;
}

bool InputManager::isHeld(unsigned char key) const {
  return keys[key];
}