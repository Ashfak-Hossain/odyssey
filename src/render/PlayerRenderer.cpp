#include "render/PlayerRenderer.h"

#include "ColorPalette.h"

void PlayerRenderer::draw(const Player& player, const Renderer& renderer) const {
  renderer.drawQuad(player.x,
                    player.y,
                    player.width,
                    player.height,
                    PLAYER_COLOR_R,
                    PLAYER_COLOR_G,
                    PLAYER_COLOR_B);
}