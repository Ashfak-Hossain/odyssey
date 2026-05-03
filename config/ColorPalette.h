#ifndef COLOR_PALETTE_H
#define COLOR_PALETTE_H

// ── Player ───────────────────────────────────────────────
constexpr float PLAYER_COLOR_R = 1.0f;
constexpr float PLAYER_COLOR_G = 0.3f;
constexpr float PLAYER_COLOR_B = 0.1f;

// ── Tile border ──────────────────────────────────────────
constexpr float TILE_BORDER_DARKNESS = 0.5f;  // border = tile color * this factor

// ── HUD health squares ───────────────────────────────────
constexpr float HUD_HEALTH_ALIVE_R = 0.90f;
constexpr float HUD_HEALTH_ALIVE_G = 0.15f;
constexpr float HUD_HEALTH_ALIVE_B = 0.15f;

constexpr float HUD_HEALTH_LOST_R = 0.25f;
constexpr float HUD_HEALTH_LOST_G = 0.25f;
constexpr float HUD_HEALTH_LOST_B = 0.25f;

// ── HUD key icon ─────────────────────────────────────────
constexpr float HUD_KEY_ACTIVE_R = 1.00f;
constexpr float HUD_KEY_ACTIVE_G = 0.85f;
constexpr float HUD_KEY_ACTIVE_B = 0.00f;

constexpr float HUD_KEY_INACTIVE_R = 0.30f;
constexpr float HUD_KEY_INACTIVE_G = 0.30f;
constexpr float HUD_KEY_INACTIVE_B = 0.30f;

// ── Exit door ────────────────────────────────────────────
constexpr float EXIT_LOCKED_FILL_R = 0.80f;
constexpr float EXIT_LOCKED_FILL_G = 0.10f;
constexpr float EXIT_LOCKED_FILL_B = 0.10f;

constexpr float EXIT_UNLOCKED_FILL_R = 0.10f;
constexpr float EXIT_UNLOCKED_FILL_G = 0.80f;
constexpr float EXIT_UNLOCKED_FILL_B = 0.10f;

constexpr float EXIT_LOCKED_BORDER_R = 0.50f;
constexpr float EXIT_LOCKED_BORDER_G = 0.05f;
constexpr float EXIT_LOCKED_BORDER_B = 0.05f;

constexpr float EXIT_UNLOCKED_BORDER_R = 0.05f;
constexpr float EXIT_UNLOCKED_BORDER_G = 0.50f;
constexpr float EXIT_UNLOCKED_BORDER_B = 0.05f;

constexpr float EXIT_BORDER_LINE_WIDTH = 3.0f;

// ── Sky clear color (glClearColor) ───────────────────────
constexpr float SKY_CLEAR_R = 0.4f;
constexpr float SKY_CLEAR_G = 0.7f;
constexpr float SKY_CLEAR_B = 1.0f;

#endif  // COLOR_PALETTE_H