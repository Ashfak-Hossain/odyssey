#include "systems/CollectibleSystem.h"

void CollectibleSystem::update(Player& player, std::vector<Key>& keys) const {
  Rect playerRect = player.getRect();
  for (auto& key : keys) {
    if (!key.collected && playerRect.overlaps(key.getRect())) {
      key.collected = true;
      player.hasKey = true;
    }
  }
}