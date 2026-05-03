#ifndef WORLD_RENDERER_H
#define WORLD_RENDERER_H

#include <vector>

#include "entities/Key.h"
#include "entities/Rect.h"
#include "entities/Tile.h"
#include "render/Renderer.h"

/**
 * @brief Draws tiles, collectible keys, and the exit door in world space.
 * All methods must be called after camera transform is applied.
 */
class WorldRenderer {
 public:
  /**
   * @brief Draw tiles in the world coords
   *
   * @param tiles list of Tiles to draw
   * @param renderer renderer method
   */
  void drawTiles(const std::vector<Tile>& tiles, const Renderer& renderer) const;

  /**
   * @brief Draw keys in the world coords
   *
   * @param keys list of keys to draw
   * @param renderer renderer method
   */
  void drawKeys(const std::vector<Key>& keys, const Renderer& renderer) const;

  /**
   * @brief
   *
   * @param locked true = needs key (red), false = open (green)
   * @param exitDoor bounding box of exitdoor
   * @param renderer
   */
  void drawExit(const Rect& exitDoor, bool locked, const Renderer& renderer) const;
};

#endif  // WORLD_RENDERER_H