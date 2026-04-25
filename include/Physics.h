#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>

#include "Player.h"
#include "Tile.h"

/**
 * @brief
 * The split-axis approach:
 * update() moves X → resolves X → moves Y → resolves Y
 */
class Physics {
 public:
  void update(Player& player, const std::vector<Tile>& tiles, float deltaTime);

 private:
  void resolveX(Player& player, const Tile& tile);
  void resolveY(Player& player, const Tile& tile);
};

#endif  // PHYSICS_H