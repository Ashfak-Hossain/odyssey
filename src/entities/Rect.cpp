#include "entities/Rect.h"

using namespace std;

#include <algorithm>

bool Rect::overlaps(const Rect& other) const {
  bool isColliding = left() < other.right() && right() > other.left() && bottom() < other.top() &&
                     top() > other.bottom();

  return isColliding;
}

float Rect::overlapX(const Rect& other) const {
  float overlapLeft  = max(left(), other.left());
  float overlapRight = min(right(), other.right());

  return overlapRight - overlapLeft;
}

float Rect::overlapY(const Rect& other) const {
  float overlapBottom = max(bottom(), other.bottom());
  float overlapTop    = min(top(), other.top());

  return overlapTop - overlapBottom;
}