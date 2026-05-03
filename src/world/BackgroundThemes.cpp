#include "world/BackgroundThemes.h"

#include "Config.h"

static void addHillRow(
    ParallaxLayer& layer, float baseY, float peak, int count, float r, float g, float b) {
  float segW = WORLD_WIDTH / count;
  for (int i = 0; i < count; i++) {
    float left  = i * segW;
    float mid   = (i + 0.5f) * segW;
    float right = (i + 1.0f) * segW;
    layer.shapes.push_back({left, baseY, mid, baseY + peak, right, baseY, r, g, b});
  }
}

// --------------- build ---------------
void BackgroundThemes::build(int levelIndex, std::vector<ParallaxLayer>& layers) {
  layers.clear();
  switch (levelIndex % 3) {
    case 0:
      buildOcean(layers);
      break;
    case 1:
      buildDesert(layers);
      break;
    default:
      buildMountain(layers);
      break;
  }
}

// --------------- ocean ---------------
void BackgroundThemes::buildOcean(std::vector<ParallaxLayer>& layers) {
  ParallaxLayer sky(BACKGROUND_LAYER_1_SPEED);
  sky.bands.push_back({HORIZON_Y, (float)WINDOW_HEIGHT, 0.20f, 0.45f, 0.80f});  // deep blue
  sky.bands.push_back({GROUND_SURFACE_Y, HORIZON_Y, 0.55f, 0.75f, 0.95f});      // light blue
  layers.push_back(sky);

  ParallaxLayer mid(BACKGROUND_LAYER_2_SPEED);
  addHillRow(mid, GROUND_SURFACE_Y, HORIZON_Y * 0.55f, 8, 0.20f, 0.50f, 0.75f);  // medium blue
  layers.push_back(mid);

  ParallaxLayer near(BACKGROUND_LAYER_3_SPEED);
  addHillRow(near, GROUND_SURFACE_Y, HORIZON_Y * 0.30f, 14, 0.12f, 0.35f, 0.60f);  // dark blue
  layers.push_back(near);
}

// --------------- desert ---------------
void BackgroundThemes::buildDesert(std::vector<ParallaxLayer>& layers) {
  ParallaxLayer sky(BACKGROUND_LAYER_1_SPEED);
  sky.bands.push_back({HORIZON_Y, (float)WINDOW_HEIGHT, 0.85f, 0.60f, 0.30f});  // warm orange
  sky.bands.push_back({GROUND_SURFACE_Y, HORIZON_Y, 0.95f, 0.80f, 0.50f});      // pale sand
  layers.push_back(sky);

  ParallaxLayer mid(BACKGROUND_LAYER_2_SPEED);
  addHillRow(mid, GROUND_SURFACE_Y, HORIZON_Y * 0.55f, 8, 0.70f, 0.50f, 0.25f);  // tan
  layers.push_back(mid);

  ParallaxLayer near(BACKGROUND_LAYER_3_SPEED);
  addHillRow(near, GROUND_SURFACE_Y, HORIZON_Y * 0.30f, 14, 0.55f, 0.38f, 0.18f);  // dark brown
  layers.push_back(near);
}

// --------------- mountain ---------------
void BackgroundThemes::buildMountain(std::vector<ParallaxLayer>& layers) {
  ParallaxLayer sky(BACKGROUND_LAYER_1_SPEED);
  sky.bands.push_back({HORIZON_Y, (float)WINDOW_HEIGHT, 0.55f, 0.65f, 0.80f});  // slate blue
  sky.bands.push_back({GROUND_SURFACE_Y, HORIZON_Y, 0.75f, 0.82f, 0.90f});      // pale grey-blue
  layers.push_back(sky);

  ParallaxLayer mid(BACKGROUND_LAYER_2_SPEED);
  addHillRow(mid, GROUND_SURFACE_Y, HORIZON_Y * 0.55f, 8, 0.50f, 0.50f, 0.55f);  // medium grey
  layers.push_back(mid);

  ParallaxLayer near(BACKGROUND_LAYER_3_SPEED);
  addHillRow(near, GROUND_SURFACE_Y, HORIZON_Y * 0.30f, 14, 0.35f, 0.38f, 0.40f);  // dark grey
  layers.push_back(near);
}
