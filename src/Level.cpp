#include "Level.h"

#include "Config.h"

Level::Level() : worldWidth(WORLD_WIDTH), name("test") {
}

void Level::loadTest() {
  buildBackground();

  tiles = {
      {0, GROUND_Y, 900, GROUND_TILE_HEIGHT, 0.35f, 0.65f, 0.25f},
      {1000, GROUND_Y, 900, GROUND_TILE_HEIGHT, 0.35f, 0.65f, 0.25f},
      {250, 120, 180, 20, 0.55f, 0.40f, 0.25f},
      {420, 80, 180, 20, 0.55f, 0.40f, 0.25f},
      {550, 220, 180, 20, 0.55f, 0.40f, 0.25f},
      {820, 320, 180, 20, 0.55f, 0.40f, 0.25f},
      {1100, 180, 180, 20, 0.55f, 0.40f, 0.25f},
      {400, 340, 120, 20, 0.70f, 0.30f, 0.30f},
      {720, 20, 20, 100, 0.30f, 0.30f, 0.70f},
  };
}

void Level::buildBackground() {
  bgLayers.clear();

  //! ============== Demo BG ==============
  {
    ParallaxLayer sky(BACKGROUND_LAYER_1_SPEED);
    sky.bands.push_back({350, (float)WINDOW_HEIGHT, 0.2, 0.45, 0.80});
    sky.bands.push_back({(float)GROUND_SURFACE_Y, 350, 0.50f, 0.72f, 0.95f});
    bgLayers.push_back(sky);
  }

  {
    ParallaxLayer mountains(BACKGROUND_LAYER_2_SPEED);

    // Dark purple-grey mountain color — desaturated for distance
    float mr = 0.40f, mg = 0.35f, mb = 0.50f;

    // Spread mountains across the full world width.
    // Each mountain: base at ground surface, peak varies for natural look.
    float peaks[] = {320, 260, 380, 300, 340, 270, 360, 290, 320, 350};
    float spacing = WORLD_WIDTH / 10.0f;  // 10 mountains across the world

    for (int i = 0; i < 10; i++) {
      float baseX = i * spacing;
      float halfW = spacing * 0.7f;  // mountains slightly overlap
      float peakY = GROUND_SURFACE_Y + peaks[i % 10];

      mountains.shapes.push_back({baseX - halfW,
                                  GROUND_SURFACE_Y,  // bottom left
                                  baseX + halfW,
                                  GROUND_SURFACE_Y,  // bottom right
                                  baseX,
                                  peakY,  // peak
                                  mr,
                                  mg,
                                  mb});
    }

    bgLayers.push_back(mountains);
  }

  {
    ParallaxLayer hills(BACKGROUND_LAYER_3_SPEED);

    // Muted dark green — in shadow compared to the lit ground
    float hr = 0.20f, hg = 0.50f, hb = 0.20f;

    float spacing   = WORLD_WIDTH / 14.0f;  // more hills, smaller
    float heights[] = {100, 80, 120, 90, 110, 85, 105, 95, 115, 75, 130, 88, 98, 108};

    for (int i = 0; i < 14; i++) {
      float baseX = i * spacing;
      float halfW = spacing * 0.65f;
      float peakY = GROUND_SURFACE_Y + heights[i % 14];

      hills.shapes.push_back({baseX - halfW,
                              GROUND_SURFACE_Y,
                              baseX + halfW,
                              GROUND_SURFACE_Y,
                              baseX,
                              peakY,
                              hr,
                              hg,
                              hb});
    }

    bgLayers.push_back(hills);
  }
  //! ============== Demo BG ==============
}

/**
 * @brief render the tiles and objects in world space.
 */
void Level::render() const {
  for (const auto& tile : tiles) {
    tile.render();
  }
}

/**
 * @brief Each layer render with its own glLoadIdentity, glTranslatef separately.
 *
 * @param cameraX The horizontal position of the camera.
 *
 * @note Must be called before full camera transform
 */
void Level::renderBackground(float cameraX) const {
  for (const auto& layer : bgLayers) {
    layer.render(cameraX);
  }
}