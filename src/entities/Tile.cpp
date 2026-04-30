#include "entities/Tile.h"

#include "utils/Platform.h"

Rect Tile::getRect() const {
  return {x, y, width, height};
}

void Tile::render() const {
  glColor3f(r, g, b);
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();

  glColor3f(r * TILE_BORDER_DARKNESS, g * TILE_BORDER_DARKNESS, b * TILE_BORDER_DARKNESS);
  glBegin(GL_LINE_LOOP);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();
}