#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Camera.h"
#include "HUD.h"
#include "InputManager.h"
#include "Level.h"
#include "LevelManager.h"
#include "Physics.h"
#include "Player.h"
#include "Tile.h"

enum class GameState { PLAYING, FADING_OUT, FADING_IN };

class Game {
  Player       player;
  LevelManager levelManager;
  Camera       camera;
  Physics      physics;
  InputManager inputManager;
  HUD          hud;

  GameState              state           = GameState::PLAYING;
  float                  transitionAlpha = 0.0f;
  float                  transitionTimer = 0.0f;
  static constexpr float FADE_DURATION   = 0.5f;

 public:
  Game();

  /**
   * @brief Initializes OpenGL and game system
   * sets up:
   * - clear color to sky blue
   * - Orthographic projection
   * - LevelManager with player spawning
   * - Initial camera position on player
   *   - this is for not getting the snap on the first frame
   *
   * @pre Must be called once before game loop starts
   */
  void init();

  /**
   * @brief Update the game state every frame with fixed timestep
   *
   * Update order:
   * - check if all levels are complete or not
   * - Handle continuous input(A/D) in every frame
   * - Physics applied in the current level
   * - Level progression (exit reach, next level)
   * - camera follows player in world area
   *
   * @param deltaTime Time elapsed since the last frame update(in seconds).
   */
  void update(float deltaTime);

  /**
   * @brief Renders the complete frame for current camera transform
   *
   * Render layers (back-to-front):
   * - Background parallax (camera.x offset only)
   * - Apply full camera transform for camera effect
   * - tiles / block, Player, exit
   */
  void render();

  /**
   * @brief Handle key down events. Space for jump, Esc for exit.
   *
   * @param key ascii code of key
   * @params x, y = mouse position.
   */
  void handleKeyUp(unsigned char key, int x, int y);

  /**
   * @brief Handle key down events.
   *
   * @param key ascii code of key
   * @params x, y = mouse position.
   */
  void handleKeyDown(unsigned char key, int x, int y);
};

#endif  // GAME_H