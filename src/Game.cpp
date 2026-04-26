#include "Game.h"

#include <cstdlib>

#include "Config.h"
#include "Platform.h"

/**
 * @brief Construct a new Game:: Game object
 */
Game::Game() {
}

/**
 * @brief Initialize the game.
 * - this method will be called once at the start of the game.
 * - set the clear color for the background.
 * - set up the projection and modelview matrices.
 * - load the level data.
 */
void Game::init() {
  glClearColor(0.4, 0.7, 1, 1);  // sky blue background

  // projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);  // left, right, bottom, top, near, far

  // modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // load level datas
  level.loadTest();
}

/**
 * @brief Update the game state every frame.
 * - This methid will be called in every frame.
 * - handles keyboard inputs.
 * - updates physics of the player.
 * - updates the camera position to follow the player.
 *
 * @param deltaTime Time elapsed since the last update(in seconds).
 */
void Game::update(float deltaTime) {
  // key press handling checked in every upate for smooth movement
  if (input.isHeld('a') || input.isHeld('A')) {
    player.moveLeft();
  } else if (input.isHeld('d') || input.isHeld('D')) {
    player.moveRight();
  } else {
    player.stopMoving();
  }

  // update physics of player and resolve collision with tiles
  physics.update(player, level.tiles, deltaTime);

  // camera follows the player
  camera.update(player.x, player.y);
}

/**
 * @brief Renders the complete game scene each frame.
 * - This method will be called in every frame.
 * - Clear thr screen.
 * - Apply camera transform to the scene.
 *    - This will move the world in the opposite direction of the camera.
 * - Render the level in world coordinate.
 * - Render the player in world coordinate.
 * - Swap the buffers to display the rendered scene.
 */
void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();  // reset modelview matrix

  camera.applyTransform();

  level.render();  // render tiles in world coordinate

  player.render();  // render in world coordinate

  //! Future UI render will be implemented here

  glutSwapBuffers();
}

/**
 * @brief Handle key down events. Space for jump, Esc for exit.
 *
 * @param key ascii code of key
 * @params x, y = mouse position.
 */
void Game::handleKeyDown(unsigned char key, int x, int y) {
  input.keyDown(key);

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
 * @params x, y = mouse position.
 */
void Game::handleKeyUp(unsigned char key, int x, int y) {
  input.keyUp(key);
}