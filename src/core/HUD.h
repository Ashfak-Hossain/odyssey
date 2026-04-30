#ifndef HUD_H
#define HUD_H

#include "world/LevelManager.h"
#include "entities/Player.h"

/**
 * @brief Renders the in-game HUD in screen space (health, key indicator, level name).
 */
class HUD {
 public:
  HUD(const Player& player, const LevelManager& levelManager);

  void render(float screenW, float screenH) const;

 private:
  const Player&       player;
  const LevelManager& levelManager;
};

#endif  // HUD_H
