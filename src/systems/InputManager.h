#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

/**
 * @brief The InputManager class manages the input state of the game.
 * tracks keyboard input.
 */
class InputManager {
 private:
  bool keys[256];  // one slot per key code (unsigned char range 0–255)

 public:
  InputManager();

  void keyDown(unsigned char key);       // called by GLUT keyboard callback on press
  void keyUp(unsigned char key);         // called by GLUT keyboard callback on release
  bool isHeld(unsigned char key) const;  // returns true while key is held down
};

#endif  // INPUTMANAGER_H