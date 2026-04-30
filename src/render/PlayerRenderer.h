#ifndef PLAYER_RENDERER_H
#define PLAYER_RENDERER_H

#include "entities/Player.h"
#include "render/Renderer.h"

/**
 * @brief Draws the player in world space.
 * @note called after camera transform is applied.
 */
class PlayerRenderer {
 public:
  /**
   * @brief Draw the player
   *
   * @param player player object
   * @param renderer renderer method
   */
  void draw(const Player& player, const Renderer& renderer) const;
};

#endif  // PLAYER_RENDERER_H