#include "entities/Key.h"

Rect Key::getRect() const {
  return {x, y, width, height};
}
