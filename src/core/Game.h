#ifndef GAME_H
#define GAME_H

#include <vector>

#include "core/GameState.h"
#include "entities/Player.h"
#include "render/BackgroundRenderer.h"
#include "render/HudRenderer.h"
#include "render/PlayerRenderer.h"
#include "render/Renderer.h"
#include "render/TransitionRenderer.h"
#include "render/WorldRenderer.h"
#include "systems/Camera.h"
#include "systems/CollectibleSystem.h"
#include "systems/InputHandler.h"
#include "systems/InputManager.h"
#include "systems/Physics.h"
#include "systems/ProgressionSystem.h"
#include "systems/RespawnSystem.h"
#include "systems/TransitionSystem.h"
#include "world/LevelManager.h"

class Game {
  // data
  Player       player;
  LevelManager levelManager;

  // systems
  Camera            camera;
  Physics           physics;
  InputManager      inputManager;
  InputHandler      inputHandler;
  TransitionSystem  transitionSystem;
  CollectibleSystem collectibleSystem;
  RespawnSystem     respawnSystem;
  ProgressionSystem progressionSystem;

  // renderers
  Renderer           renderer;
  PlayerRenderer     playerRenderer;
  WorldRenderer      worldRenderer;
  BackgroundRenderer backgroundRenderer;
  HudRenderer        hudRenderer;
  TransitionRenderer transitionRenderer;

 public:
  Game();

  /**
   * @brief Initializes OpenGL and game system
   * sets up:
   * - clear color to sky blue
   * - Orthographic projection
   * - LevelManager initialize level with player spawning
   * - Initial camera position on player
   *   - this is for not getting the snap on the first frame
   *
   * @note Must be called once before game loop starts
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