#include "Game.h"

#include <cstdlib>

#include "Platform.h"

Game::Game() {
  // initialize all keys to false
  for (int i = 0; i < 256; i++) {
    keyPressed[i] = false;
  }
}

void Game::init() {
  glClearColor(0.4, 0.7, 1, 1);

  // projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);

  // modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Game::update(float deltaTime) {
  // key press handling checked in every upate for smooth movement
  if (keyPressed['a'] or keyPressed['A']) {
    player.moveLeft();
  } else if ((keyPressed['d'] or keyPressed['D'])) {
    player.moveRight();
  } else {
    player.stopMoving();
  }

  // update player in every game update call
  player.update(deltaTime);

  // camera follows the player
  camera.update(player.x, player.y);
}

void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT);

  glLoadIdentity();  // reset modelview matrix

  camera.applyTransform();

  // simple line
  glColor3f(0.2f, 0.8f, 0.2f);
  glLineWidth(3.0f);
  glBegin(GL_LINES);
  glVertex2f(0, GROUND_Y);
  glVertex2f(WINDOW_WIDTH, GROUND_Y);
  glEnd();

  player.render();  // render in world coordinate

  //! Future UI render will be implemented here

  glutSwapBuffers();
}

/**
 * @brief Handle key down events. Space for jump, Esc for exit.
 *
 * @param key ascii code of key
 * @param x mouse x position
 * @param y mouse y position
 */
void Game::handleKeyDown(unsigned char key, int x, int y) {
  keyPressed[key] = true;
  if (key == ' ') {
    player.jump();
  }
  if (key == 27) {
    exit(0);
  }
}

/**
 * @brief Handle key up events.
 *
 * @param key ascii code of key
 * @param x mouse x position
 * @param y mouse y position
 */
void Game::handleKeyUp(unsigned char key, int x, int y) {
  keyPressed[key] = false;
}