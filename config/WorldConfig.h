#ifndef WORLD_CONFIG_H
#define WORLD_CONFIG_H

constexpr float GROUND_Y           = 0.0f;
constexpr float GROUND_TILE_HEIGHT = 20.0f;
constexpr float GROUND_SURFACE_Y   = GROUND_Y + GROUND_TILE_HEIGHT;
constexpr float HORIZON_Y          = 350.0f;  // y,here sky top color meets sky bottom color

constexpr float BACKGROUND_LAYER_1_SPEED = 0.0f;
constexpr float BACKGROUND_LAYER_2_SPEED = 0.2f;
constexpr float BACKGROUND_LAYER_3_SPEED = 0.5f;

#endif  // WORLD_CONFIG_H