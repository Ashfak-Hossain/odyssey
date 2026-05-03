#ifndef HUD_CONFIG_H
#define HUD_CONFIG_H

// Health squares
constexpr float HUD_HEALTH_SQUARE_SIZE = 20.0f;  // width and height of each health square
constexpr float HUD_HEALTH_SPACING     = 8.0f;   // gap of health squares
constexpr float HUD_LEFT_PAD           = 10.0f;  // distance from left edge of screen
constexpr float HUD_TOP_PAD            = 30.0f;  // distance from top edge of screen

// Key icon
constexpr float HUD_KEY_ICON_SIZE     = 16.0f;  // width and height of key icon
constexpr float HUD_KEY_ICON_X_OFFSET = 6.0f;   // gap between last health square and key icon
constexpr float HUD_KEY_ICON_Y_OFFSET = 2.0f;   // key icon sits slightly above square baseline

// Level name text
constexpr float HUD_TEXT_Y_OFFSET = 18.0f;  // pixels below health row baseline

#endif  // HUD_CONFIG_H