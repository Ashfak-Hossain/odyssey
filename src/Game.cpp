#include "Game.h"

#include <cstdlib>

#include "Config.h"
#include "Game.h"
#include "Platform.h"

Game::Game() {
}

void Game::init() {
  glClearColor(0.4, 0.7, 1, 1);  // sky blue background

  glMatrixMode(GL_PROJECTION);  // projection matrix
  glLoadIdentity();
  glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);  // left, right, bottom, top, near, far
  glMatrixMode(GL_MODELVIEW);                         // modelview matrix
  glLoadIdentity();

  // loads the level and spawn the player
  levelManager.init(player);

  // update the camera for player
  camera.update(player.x, player.y, levelManager.currentLevel().worldWidth);
}

void Game::update(float deltaTime) {
  if (levelManager.isComplete()) {
    return;
  }

  // key press handling checked in every upate for smooth movement
  if (inputManager.isHeld('a') || inputManager.isHeld('A')) {
    player.moveLeft();
  } else if (inputManager.isHeld('d') || inputManager.isHeld('D')) {
    player.moveRight();
  } else {
    player.stopMoving();
  }

  // apply physics in the current level
  Level& lvl = levelManager.currentLevel();
  physics.update(player, lvl.tiles, deltaTime);

  // check level progeression
  levelManager.update(player);

  // update the camera for player
  camera.update(player.x, player.y, lvl.worldWidth);
}

void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT);

  Level& lvl = levelManager.currentLevel();

  lvl.renderBackground(camera.x);  // render bg

  glLoadIdentity();  // reset modelview matrix
  camera.applyTransform();

  lvl.renderForeground();  // render tiles in world coordinate
  lvl.renderExit();
  player.render();  // render in world coordinate

  //! Future UI render will be implemented here

  glutSwapBuffers();
}

void Game::handleKeyDown(unsigned char key, int x, int y) {
  inputManager.keyDown(key);

  if (key == ' ') {
    player.jump();
  }
  if (key == 27) {
    exit(0);
  }
}

void Game::handleKeyUp(unsigned char key, int x, int y) {
  inputManager.keyUp(key);
}