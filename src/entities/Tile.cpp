#include "entities/Tile.h"

Rect Tile::getRect() const {
  return {x, y, width, height};
}
