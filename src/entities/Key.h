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

  /**
   * @brief Get the Rect object
   * @return Rect
   */
  Rect getRect() const;
};

#endif  // KEY_H