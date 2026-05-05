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
  float keyAngle = 0.0f;

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
   * @param deltaTime Time elapsed since the last frame update(in seconds).
   */
  void drawKeys(const std::vector<Key>& keys, const Renderer& renderer, float deltaTime);

  /**
   * @brief
   *
   * @param locked true = needs key (red), false = open (green)
   * @param exitDoor bounding box of exitdoor
   * @param renderer
   */
  void drawExit(const Rect& exitDoor, bool locked, const Renderer& renderer) const;

 private:
  static void drawKeyBox(float hw, float hh, float hd);
  static void drawKeyFace(float r,
                          float g,
                          float b,
                          float x0,
                          float y0,
                          float z0,
                          float x1,
                          float y1,
                          float z1,
                          float x2,
                          float y2,
                          float z2,
                          float x3,
                          float y3,
                          float z3);
  static void drawKeyFaceOutline(float x0,
                                 float y0,
                                 float z0,
                                 float x1,
                                 float y1,
                                 float z1,
                                 float x2,
                                 float y2,
                                 float z2,
                                 float x3,
                                 float y3,
                                 float z3);
};

#endif  // WORLD_RENDERER_H