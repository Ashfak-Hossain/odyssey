#include "Rect.h"

#include <algorithm>

bool Rect::overlaps(const Rect& other) const {
  bool isColliding = left() < other.right() && right() > other.left() && bottom() < other.top() &&
                     top() > other.bottom();

  return isColliding;
}

float Rect::overlapX(const Rect& other) const {
  float overlapLeft  = std::max(left(), other.left());
  float overlapRight = std::min(right(), other.right());

  return overlapRight - overlapLeft;
}

float Rect::overlapY(const Rect& other) const {
  float overlapBottom = std::max(bottom(), other.bottom());
  float overlapTop    = std::min(top(), other.top());

  return overlapTop - overlapBottom;
}