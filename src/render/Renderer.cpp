#include "render/Renderer.h"

#include "utils/Platform.h"

void Renderer::clearScreen() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::swapBuffers() const {
  glutSwapBuffers();
}

void Renderer::enableBlending() const {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::disableBlending() const {
  glDisable(GL_BLEND);
}

void Renderer::drawPixel(float x, float y, float r, float g, float b) const {
  glColor3f(r, g, b);
  glBegin(GL_POINTS);
  glVertex2f(x, y);
  glEnd();
}

void Renderer::drawMidpointLine(int x0, int y0, int x1, int y1, float r, float g, float b) const {
  int dx  = std::abs(x1 - x0);
  int dy  = std::abs(y1 - y0);
  int sx  = (x0 < x1) ? 1 : -1;
  int sy  = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  while (true) {
    drawPixel(x0, y0, r, g, b);

    if (x0 == x1 && y0 == y1) {
      break;
    }

    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void Renderer::drawQuad(float x, float y, float w, float h, float r, float g, float b) const {
  glColor3f(r, g, b);
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + w, y);
  glVertex2f(x + w, y + h);
  glVertex2f(x, y + h);
  glEnd();
}

void Renderer::drawQuadAlpha(
    float x, float y, float w, float h, float r, float g, float b, float a) const {
  glColor4f(r, g, b, a);
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + w, y);
  glVertex2f(x + w, y + h);
  glVertex2f(x, y + h);
  glEnd();
}

void Renderer::drawQuadOutline(
    float x, float y, float w, float h, float r, float g, float b, float lineWidth) const {
  glLineWidth(lineWidth);
  glColor3f(r, g, b);
  glBegin(GL_LINE_LOOP);
  glVertex2f(x, y);
  glVertex2f(x + w, y);
  glVertex2f(x + w, y + h);
  glVertex2f(x, y + h);
  glEnd();
}

void Renderer::drawTriangle(
    float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) const {
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glVertex2f(x3, y3);
  glEnd();
}

void Renderer::drawText(
    float x, float y, const std::string& text, float r, float g, float b) const {
  glColor3f(r, g, b);
  glRasterPos2f(x, y);
  for (char c : text) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
}

void Renderer::pushMatrix() const {
  glPushMatrix();
}

void Renderer::popMatrix() const {
  glPopMatrix();
}

void Renderer::loadIdentity() const {
  glLoadIdentity();
}

void Renderer::translate(float x, float y) const {
  glTranslatef(x, y, 0.0f);
}

void Renderer::drawTransition(float alpha, float screenW, float screenH) const {
  if (alpha <= 0.0f) {
    return;
  }
  pushMatrix();
  loadIdentity();
  enableBlending();
  drawQuadAlpha(0.0f, 0.0f, screenW, screenH, 0.0f, 0.0f, 0.0f, alpha);
  disableBlending();
  popMatrix();
}