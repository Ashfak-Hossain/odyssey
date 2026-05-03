#ifndef TRANSITION_SYSTEM_H
#define TRANSITION_SYSTEM_H

#include "core/GameState.h"
#include "entities/Player.h"
#include "world/LevelManager.h"

/**
 * @brief This is a state machine which makes the black-screen fade between levels.
 * States:  PLAYING → FADING_OUT → FADING_IN → PLAYING
 */
class TransitionSystem {
 private:
  LevelManager& levelManager;
  Player&       player;

  GameState state           = GameState::PLAYING;
  float     transitionAlpha = 0.0f;  // current overlay opacity [0.0, 1.0]
  float     transitionTimer = 0.0f;  // current time (in seconds)

 public:
  TransitionSystem(LevelManager& levelManager, Player& player);

  /**
   * @brief start fading if state is not `GameState::PLAYING`
   * - this works when game is freezed by `!transitionSystem.allowsGameplay()`
   *
   * @param deltaTime Time elapsed since the last frame update(in seconds).
   */
  void update(float deltaTime);

  /**
   * @brief Set the state `GameState::FADING_OUT` , transition timer reset to 0.
   */
  void startFade();

  /**
   * @return true: if game is in `PLAYING` state
   * @return false: if game is not in `PLAYING` state
   */
  bool allowsGameplay() const;

  // Current overlay opacity [0, 1]; fed to Renderer::drawTransition() each frame.
  /**
   * @brief get the current overlay opacity [0, 1].
   *   - used in `renderer.drawTransition()`
   *
   * @return float: current transitionAlpha value
   */
  float getAlpha() const;
};

#endif  // TRANSITION_SYSTEM_H