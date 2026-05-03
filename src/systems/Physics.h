#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>

#include "entities/Player.h"
#include "entities/Tile.h"

/**
 * @brief Stateless Physics system
 * The split-axis approach: update() -> moves X → resolves X → moves Y → resolves Y collisions.
 */
class Physics {
 public:
  // Applies gravity, moves the player, and resolves tile collisions for one frame.
  void update(Player& player, const std::vector<Tile>& tiles, float deltaTime);

 private:
  /**
   * @brief Resolve collision on the X-axis.
   * - Pushes player out of a tile horizontally; zeroes vx on contact.
   *
   * @param tile The tile to check collision with.
   */
  void resolveX(Player& player, const Tile& tile);

  /**
   * @brief Resolve collision on the Y-axis.
   * - Pushes player out of a tile vertically; zeroes vy and sets onGround when landing on top.
   *
   * @param tile The tile to check collision with.
   */
  void resolveY(Player& player, const Tile& tile);
};

#endif  // PHYSICS_H