#include "Game.h"
#include "Platform.h"

Game game;

void display() {
  game.render();
}

/**
 * @brief handles key press events.
 */
void keyboard(unsigned char key, int x, int y) {
  game.handleKeyDown(key, x, y);
}

/**
 * @brief handles key release events.
 */
void keyboardUp(unsigned char key, int x, int y) {
  game.handleKeyUp(key, x, y);
}

/**
 * @brief update game logic at a fixed time and request a redraw.
 * This idle function runs continuously when no other events are being processed. so we can see the
 * objects running smoothly. if the game runs in 60fps, the deltaTime will be around 0.016s.
 *
 * @note The static lastTime variable persists across calls to maintain accurate deltaTime.
 * @note Relies on global 'game' object for state updates.
 */
void idle() {
  float static lastTime = glutGet(GLUT_ELAPSED_TIME);
  float currentTime     = glutGet(GLUT_ELAPSED_TIME);
  float deltaTime       = (currentTime - lastTime) / 1000.0f;

  if (deltaTime > 0.05f) {
    deltaTime = 0.05f;
  }

  lastTime = currentTime;

  game.update(deltaTime);
  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  int screenWidth  = glutGet(GLUT_SCREEN_WIDTH);
  int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition((screenWidth - WINDOW_WIDTH) / 2, (screenHeight - WINDOW_HEIGHT) / 2);
  glutCreateWindow(WINDOW_TITLE);

  game.init();

  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);

  glutMainLoop();

  return 0;
}