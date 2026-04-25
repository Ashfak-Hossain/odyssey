#include "InputManager.h"

// Constructor initializes all keys to false(not pressed)
InputManager::InputManager() {
  for (int i = 0; i < 256; ++i) {
    keys[i] = false;
  }
}

// Mark a key as pressed
void InputManager::keyDown(unsigned char key) {
  keys[key] = true;
}

// Mark a key as released
void InputManager::keyUp(unsigned char key) {
  keys[key] = false;
}

// Check if a key is currently held down
bool InputManager::isHeld(unsigned char key) const {
  return keys[key];
}