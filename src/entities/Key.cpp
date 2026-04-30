#include "entities/Key.h"

#include "utils/Platform.h"

Rect Key::getRect() const {
  return {x, y, width, height};
}

void Key::render() const {
  if (collected) {
    return;
  }

  glColor3f(1.0f, 0.85f, 0.0f);
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();

  glColor3f(0.7f, 0.55f, 0.0f);
  glBegin(GL_LINE_LOOP);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();
}
