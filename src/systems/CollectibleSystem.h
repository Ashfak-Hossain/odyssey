#ifndef COLLECTIBLE_SYSTEM_H
#define COLLECTIBLE_SYSTEM_H

#include <vector>

#include "entities/Key.h"
#include "entities/Player.h"

/**
 * @brief Handles key pickup logic each frame.
 * Checks player AABB against every uncollected key.
 * Sets key.collected and player.hasKey on overlap.
 */
class CollectibleSystem {
 public:
  void update(Player& player, std::vector<Key>& keys) const;
};

#endif  // COLLECTIBLE_SYSTEM_H