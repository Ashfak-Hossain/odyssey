#include "systems/TransitionSystem.h"

#include "TransitionConfig.h"

TransitionSystem::TransitionSystem(LevelManager& levelManager, Player& player)
    : levelManager(levelManager), player(player) {
}

void TransitionSystem::update(float deltaTime) {
  // Nothing to do while state is playing
  if (state == GameState::PLAYING) {
    return;
  }

  transitionTimer += deltaTime;

  if (state == GameState::FADING_OUT) {
    // transitionAlpha increases from 0 → 1 in FADE_DURATION seconds.
    transitionAlpha = transitionTimer / FADE_DURATION;
    if (transitionAlpha > 1.0f) {
      transitionAlpha = 1.0f;
    }

    // change level at full dark overlay
    if (transitionTimer >= FADE_DURATION) {
      levelManager.advance(player);
      state           = GameState::FADING_IN;
      transitionTimer = 0.0f;  // restart timer for the fade-in phase
    }

  } else if (state == GameState::FADING_IN) {
    // transitionAlpha decreases from 1 → 0 over FADE_DURATION seconds.
    transitionAlpha = 1.0f - transitionTimer / FADE_DURATION;
    if (transitionAlpha < 0.0f) {
      transitionAlpha = 0.0f;
    }

    // Fade complete — return to play
    if (transitionTimer >= FADE_DURATION) {
      transitionAlpha = 0.0f;
      state           = GameState::PLAYING;
    }
  }
}

void TransitionSystem::startFade() {
  state           = GameState::FADING_OUT;
  transitionTimer = 0.0f;
}

bool TransitionSystem::allowsGameplay() const {
  return state == GameState::PLAYING;
}

float TransitionSystem::getAlpha() const {
  return transitionAlpha;
}
