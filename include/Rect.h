#ifndef RECT_H
#define RECT_H

/**
 * @brief Axis-Aligned Bounding Box(AABB) structure for object detection
 *
 * x, y = bottom-left corner
 */
struct Rect {
  float x, y, width, height;

  // edges
  float left() const {
    return x;
  }
  float right() const {
    return x + width;
  }
  float top() const {
    return y + height;
  }
  float bottom() const {
    return y;
  }

  // center
  float centerX() const {
    return x + width / 2.0f;
  }
  float centerY() const {
    return y + height / 2.0f;
  }

  /**
   * @brief Check if this rectangle overlaps with another rectangle
   * @param other The other rectangle
   * @return true if collides, false otherwise;
   */
  bool overlaps(const Rect& other) const;

  /**
   * @brief check if this rectangle collides with other in x-axis
   *
   * @param other The other rectangle
   * @return the overlap distance in x-axis.
   */
  float overlapX(const Rect& other) const;

  /**
   * @brief check if this rectangle collides with other in y-axis
   *
   * @param other The other rectangle
   * @return the overlap distance in y-axis.
   */
  float overlapY(const Rect& other) const;
};

#endif