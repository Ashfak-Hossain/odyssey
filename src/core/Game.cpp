#include "core/Game.h"

#include <cstdlib>

#include "Config.h"
#include "utils/Platform.h"

Game::Game() : transitionSystem(levelManager, player) {
}

// ----------------------------------------------
// ------------------- Init ---------------------
// ----------------------------------------------
void Game::init() {
  glClearColor(SKY_CLEAR_R, SKY_CLEAR_G, SKY_CLEAR_B, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  levelManager.init(player);
  camera.update(player.x, player.y, levelManager.currentLevel().worldWidth);
}

// ----------------------------------------------
// ------------------- Update -------------------
// ----------------------------------------------
void Game::update(float deltaTime) {
  if (levelManager.isComplete()) {
    return;
  }

  transitionSystem.update(deltaTime);

  if (!transitionSystem.allowsGameplay()) {
    camera.update(player.x, player.y, levelManager.currentLevel().worldWidth);
    return;
  }

  inputHandler.applyMovement(player, inputManager);

  Level& lvl = levelManager.currentLevel();
  physics.update(player, lvl.tiles, deltaTime);

  collectibleSystem.update(player, lvl.keys);
  respawnSystem.update(player, levelManager);

  if (progressionSystem.update(player, levelManager)) {
    transitionSystem.startFade();
  }

  camera.update(player.x, player.y, lvl.worldWidth);
}

// ----------------------------------------------
// ------------------- Render -------------------
// ----------------------------------------------
void Game::render() {
  renderer.clearScreen();

  Level& lvl = levelManager.currentLevel();

  // Background — before camera transform
  backgroundRenderer.draw(lvl.bgLayers, camera.x, renderer);

  // Apply camera for world-space objects
  renderer.loadIdentity();
  camera.applyTransform();

  worldRenderer.drawTiles(lvl.tiles, renderer);
  worldRenderer.drawKeys(lvl.keys, renderer);
  if (lvl.hasExit) {
    worldRenderer.drawExit(lvl.exitDoor, !player.hasKey, renderer);
  }

  playerRenderer.draw(player, renderer);

  // HUD — screen space
  hudRenderer.draw(player, levelManager, WINDOW_WIDTH, WINDOW_HEIGHT, renderer);

  // Fade overlay — always last
  transitionRenderer.draw(transitionSystem.getAlpha(), WINDOW_WIDTH, WINDOW_HEIGHT, renderer);

  renderer.swapBuffers();
}

// ----------------------------------------------
// ------------------- KeyDown ------------------
// ----------------------------------------------
void Game::handleKeyDown(unsigned char key, int x, int y) {
  inputManager.keyDown(key);

  if (key == ' ' && transitionSystem.allowsGameplay()) {
    player.jump();
  }
  if (key == 27) {
    exit(0);
  }
}

// ----------------------------------------------
// ------------------- KeyUp --------------------
// ----------------------------------------------
void Game::handleKeyUp(unsigned char key, int x, int y) {
  inputManager.keyUp(key);
}