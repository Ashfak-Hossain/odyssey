#ifndef KEY_H
#define KEY_H

#include "entities/Rect.h"

/**
 * @struct Key
 * @brief a collectible key object
 */
struct Key {
  float x, y, width, height;
  bool  collected = false;

  Rect getRect() const;
  void render() const;
};

#endif  // KEY_H