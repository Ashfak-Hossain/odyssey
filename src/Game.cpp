#include "Game.h"

#include <cstdlib>

#include "Config.h"
#include "Platform.h"

/**
 * @brief Construct a new Game:: Game object
 */
Game::Game() {
  // initialize all keys to false
  for (int i = 0; i < 256; i++) {
    keyPressed[i] = false;
  }
}

/**
 * @brief Initialize the game.
 * This method will be called once at the start of the game.
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

  tiles = {
      {0, GROUND_Y, 900, GROUND_TILE_HEIGHT, 0.35f, 0.65f, 0.25f},
      {1000, GROUND_Y, 900, GROUND_TILE_HEIGHT, 0.35f, 0.65f, 0.25f},

      // random tiles
      {250, 120, 180, 20, 0.55f, 0.40f, 0.25f},
      {550, 220, 180, 20, 0.55f, 0.40f, 0.25f},
      {820, 320, 180, 20, 0.55f, 0.40f, 0.25f},
      {1100, 180, 180, 20, 0.55f, 0.40f, 0.25f},
      {400, 340, 120, 20, 0.70f, 0.30f, 0.30f},
      {720, 20, 20, 100, 0.30f, 0.30f, 0.70f},
  };
}

/**
 * @brief Resolve collision on the X-axis.
 *
 * @param tile The tile to check collision with.
 */
void Game::resolveCollisionX(Tile& tile) {
  Rect playerRect = player.getRect();
  Rect tileRect   = tile.getRect();

  // no collision, do nothing
  if (!playerRect.overlaps(tileRect)) {
    return;
  }

  float overlapX = playerRect.overlapX(tileRect);

  // by measure center of player and tile. we can get which direction player comes from and push the
  // player to the direction.
  if (playerRect.centerX() < tileRect.centerX()) {
    player.x -= overlapX;
  } else {
    player.x += overlapX;
  }

  player.vx = 0;
}

/**
 * @brief Resolve collision on the Y-axis.
 *
 * @param tile The tile to check collision with.
 */
void Game::resolveCollisionY(Tile& tile) {
  Rect playerRect = player.getRect();
  Rect tileRect   = tile.getRect();

  // no collision, do nothing
  if (!playerRect.overlaps(tileRect)) {
    return;
  }

  float overlapY = playerRect.overlapY(tileRect);
  if (playerRect.centerY() > tileRect.centerY()) {
    player.y += overlapY;
    player.vy       = 0;
    player.onGround = true;
  } else {
    player.y -= overlapY;
    player.vy = 0;
  }

  // player.vy = 0;
}

/**
 * @brief Update the game state. Serial by handle input, physics, collision and camera update.
 *  This called in every frame by main loop.
 *
 * @param deltaTime Time elapsed since the last update(in seconds).
 */
void Game::update(float deltaTime) {
  // key press handling checked in every upate for smooth movement
  if (keyPressed['a'] or keyPressed['A']) {
    player.moveLeft();
  } else if ((keyPressed['d'] or keyPressed['D'])) {
    player.moveRight();
  } else {
    player.stopMoving();
  }

  // applied gravity to player.
  player.applyGravity(deltaTime);

  // ------ X axis movement and collision ------
  // move x axis only
  player.x += player.vx * deltaTime;

  // edges of world
  if (player.x < 0) {
    player.x  = 0;
    player.vx = 0;
  }

  // resolve x-axis collision with tiles
  for (auto& tile : tiles) {
    resolveCollisionX(tile);
  }

  // ------ Y axis movement and collision ------
  // move y axis only
  player.y += player.vy * deltaTime;

  player.onGround = false;  // reset ground before collision check

  // resolve y-axis collision with tiles
  for (auto& tile : tiles) {
    resolveCollisionY(tile);
  }

  // camera follows the player
  camera.update(player.x, player.y);
}

/**
 * @brief Render the game scene every frame.
 */
void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();  // reset modelview matrix

  camera.applyTransform();

  // render tile in world coordinate
  for (auto& tile : tiles) {
    tile.render();
  }

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
 * @params x, y = mouse position.
 */
void Game::handleKeyUp(unsigned char key, int x, int y) {
  keyPressed[key] = false;
}