#ifndef TRANSITION_SYSTEM_H
#define TRANSITION_SYSTEM_H

#include "core/GameState.h"
#include "entities/Player.h"
#include "world/LevelManager.h"

/**
 * @brief manage the fade (PLAYING -> FADING_OUT → advance level → FADING_IN → PLAYING).
 *
 * Call startFade() to trigger a transition.
 * Call update(dt) every frame — it updates and calls levelManager.advance at the midpoint.
 * Call allowsGameplay() to know if normal gameplay should run this frame.
 * Call getAlpha() to get the current fade opacity for TransitionRenderer.
 */
class TransitionSystem {
 private:
  LevelManager& levelManager;
  Player&       player;

  GameState state           = GameState::PLAYING;
  float     transitionAlpha = 0.0f;
  float     transitionTimer = 0.0f;

 public:
  TransitionSystem(LevelManager& levelManager, Player& player);

  void update(float deltaTime);

  /**
   * @brief Trigger the start of a fade-out → advance → fade-in sequence.
   * No-op if a transition is already in progress.
   */
  void startFade();

  bool  allowsGameplay() const;  // true only when state == PLAYING
  float getAlpha() const;        // current fade opacity [0, 1]
};

#endif  // TRANSITION_SYSTEM_H