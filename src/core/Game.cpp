#include "core/Game.h"

#include <cstdlib>

#include "Config.h"
#include "utils/Platform.h"

Game::Game() {
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

  // Handle transition animation — block gameplay input during fades
  if (state != GameState::PLAYING) {
    transitionTimer += deltaTime;

    if (state == GameState::FADING_OUT) {
      transitionAlpha = transitionTimer / FADE_DURATION;
      if (transitionAlpha > 1.0f) {
        transitionAlpha = 1.0f;
      }

      if (transitionTimer >= FADE_DURATION) {
        levelManager.advance(player);
        state           = GameState::FADING_IN;
        transitionTimer = 0.0f;
      }

    } else if (state == GameState::FADING_IN) {
      transitionAlpha = 1.0f - transitionTimer / FADE_DURATION;
      if (transitionAlpha < 0.0f) {
        transitionAlpha = 0.0f;
      }

      if (transitionTimer >= FADE_DURATION) {
        transitionAlpha = 0.0f;
        state           = GameState::PLAYING;
      }
    }

    camera.update(player.x, player.y, levelManager.currentLevel().worldWidth);
    return;
  }

  // --- Normal gameplay ---

  if (inputManager.isHeld('a') || inputManager.isHeld('A')) {
    player.moveLeft();
  } else if (inputManager.isHeld('d') || inputManager.isHeld('D')) {
    player.moveRight();
  } else {
    player.stopMoving();
  }

  Level& lvl = levelManager.currentLevel();
  physics.update(player, lvl.tiles, deltaTime);

  // Key pickup
  Rect playerRect = player.getRect();
  for (auto& key : lvl.keys) {
    if (!key.collected && playerRect.overlaps(key.getRect())) {
      key.collected = true;
      player.hasKey = true;
    }
  }

  // Fall-off damage
  if (player.y < FALL_THRESHOLD) {
    player.takeDamage();
    if (player.health <= 0) {
      player.health = Player::MAX_HEALTH;
      levelManager.resetToFirst(player);
    }
  }

  // Level change, use fade animation instead of instant change
  if (levelManager.shouldAdvance(player)) {
    state           = GameState::FADING_OUT;
    transitionTimer = 0.0f;
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
  transitionRenderer.draw(transitionAlpha, WINDOW_WIDTH, WINDOW_HEIGHT, renderer);

  renderer.swapBuffers();
}

// ----------------------------------------------
// ------------------- KeyDown ------------------
// ----------------------------------------------
void Game::handleKeyDown(unsigned char key, int x, int y) {
  inputManager.keyDown(key);

  if (key == ' ' && state == GameState::PLAYING) {
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