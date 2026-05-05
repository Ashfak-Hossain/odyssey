#include <iostream>

#include "core/Game.h"
#include "utils/Platform.h"

Game game;

/**
 * @brief GLUT idle callback that handles the game loop.
 *
 * Invoked continuously by GLUT whenever no OS events are pending.
 * Computes the wall-clock delta since the last call, advances game logic, then
 * schedules a redisplay.
 */
void idle() {
  float static lastTime = glutGet(GLUT_ELAPSED_TIME);
  float currentTime     = glutGet(GLUT_ELAPSED_TIME);
  float deltaTime       = std::min((currentTime - lastTime) / 1000.0f, 0.05f);  // ~0.016
  lastTime              = currentTime;

  game.update(deltaTime);
  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  int screenWidth  = glutGet(GLUT_SCREEN_WIDTH);
  int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition((screenWidth - WINDOW_WIDTH) / 2, (screenHeight - WINDOW_HEIGHT) / 2);
  glutCreateWindow(WINDOW_TITLE);

  game.init();

  glutDisplayFunc([]() { game.render(); });
  glutIdleFunc(idle);
  glutKeyboardFunc([](unsigned char key, int x, int y) { game.handleKeyDown(key, x, y); });
  glutKeyboardUpFunc([](unsigned char key, int x, int y) { game.handleKeyUp(key, x, y); });

  glutMainLoop();

  return 0;
}