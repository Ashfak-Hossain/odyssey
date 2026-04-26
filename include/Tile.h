#ifndef TILE_H
#define TILE_H

#include "Rect.h"

/**
 * @brief this is the static object in the game.It just has position and size. A building block.
 *
 * x, y = bottom-left corner
 */
struct Tile {
  float x, y, width, height;  // x, y = bottom-left corner
  float r, g, b;              // color

  // returns the bounding box of this tile
  Rect getRect() const;

  // render this tile on the screen
  void render() const;
};

#endif  // TILE_H