#include "core/Game.h"

#include <cstdlib>

#include "Config.h"
#include "utils/Platform.h"

Game::Game() : hud(player, levelManager) {
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
  glClear(GL_COLOR_BUFFER_BIT);

  Level& lvl = levelManager.currentLevel();

  lvl.renderBackground(camera.x);

  glLoadIdentity();
  camera.applyTransform();

  lvl.renderForeground();
  lvl.renderKeys();
  lvl.renderExit(!player.hasKey);
  player.render();

  // HUD in screen space
  hud.render(WINDOW_WIDTH, WINDOW_HEIGHT);

  // Fade overlay (black quad over full screen)
  glPushMatrix();
  glLoadIdentity();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(0.0f, 0.0f, 0.0f, transitionAlpha);
  glBegin(GL_QUADS);
  glVertex2f(0.0f, 0.0f);
  glVertex2f((float)WINDOW_WIDTH, 0.0f);
  glVertex2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
  glVertex2f(0.0f, (float)WINDOW_HEIGHT);
  glEnd();
  glDisable(GL_BLEND);
  glPopMatrix();

  glutSwapBuffers();
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