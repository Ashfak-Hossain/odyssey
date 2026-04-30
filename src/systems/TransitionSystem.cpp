#include "systems/TransitionSystem.h"

#include "TransitionConfig.h"

TransitionSystem::TransitionSystem(LevelManager& levelManager, Player& player)
    : levelManager(levelManager), player(player) {
}

void TransitionSystem::update(float deltaTime) {
  if (state == GameState::PLAYING) {
    return;
  }

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
}

void TransitionSystem::startFade() {
  if (state != GameState::PLAYING) {
    return;
  }
  state           = GameState::FADING_OUT;
  transitionTimer = 0.0f;
}

bool TransitionSystem::allowsGameplay() const {
  return state == GameState::PLAYING;
}

float TransitionSystem::getAlpha() const {
  return transitionAlpha;
}