#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

/**
 * @brief The InputManager class manages the input state of the game.
 * tracks keyboard input.
 */
class InputManager {
 private:
  bool keys[256];

 public:
  InputManager();

  void keyDown(unsigned char key);
  void keyUp(unsigned char key);
  bool isHeld(unsigned char key) const;
};

#endif  // INPUTMANAGER_H