#ifndef HUD_RENDERER_H
#define HUD_RENDERER_H

#include "entities/Player.h"
#include "render/Renderer.h"
#include "world/LevelManager.h"

/**
 * @brief Draws the HUD in screen space (health, key icon, level name).
 * Must be called after glLoadIdentity — unaffected by camera transform.
 */
class HudRenderer {
 public:
  void draw(const Player&       player,
            const LevelManager& levelManager,
            float               screenW,
            float               screenH,
            const Renderer&     renderer) const;
};

#endif  // HUD_RENDERER_H