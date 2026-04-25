#include "Level.h"

#include "Config.h"

Level::Level() : worldWidth(WORLD_WIDTH), name("test") {
}

void Level::loadTest() {
  tiles = {
      {0, GROUND_Y, 900, GROUND_TILE_HEIGHT, 0.35f, 0.65f, 0.25f},
      {1000, GROUND_Y, 900, GROUND_TILE_HEIGHT, 0.35f, 0.65f, 0.25f},
      {250, 120, 180, 20, 0.55f, 0.40f, 0.25f},
      {550, 220, 180, 20, 0.55f, 0.40f, 0.25f},
      {820, 320, 180, 20, 0.55f, 0.40f, 0.25f},
      {1100, 180, 180, 20, 0.55f, 0.40f, 0.25f},
      {400, 340, 120, 20, 0.70f, 0.30f, 0.30f},
      {720, 20, 20, 100, 0.30f, 0.30f, 0.70f},
  };
}

void Level::render() const {
  for (const auto& tile : tiles) {
    tile.render();
  }
}