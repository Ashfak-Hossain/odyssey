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
  int dx    = std::abs(x1 - x0);
  int dy    = std::abs(y1 - y0);
  int stepX = (x0 < x1) ? 1 : -1;
  int stepY = (y0 < y1) ? 1 : -1;
  int error = dx - dy;

  while (x0 != x1 || y0 != y1) {
    drawPixel(x0, y0, r, g, b);
    int err2 = 2 * error;
    if (err2 > -dy) {
      error -= dy;
      x0 += stepX;
    }
    if (err2 < dx) {
      error += dx;
      y0 += stepY;
    }
  }
  drawPixel(x1, y1, r, g, b);
}

void Renderer::drawMidpointCircle(int cx, int cy, int radius, float r, float g, float b) const {
  int x = 0;
  int y = radius;
  int p = 1 - radius;

  while (x <= y) {
    drawPixel(cx + x, cy + y, r, g, b);
    drawPixel(cx - x, cy + y, r, g, b);
    drawPixel(cx + x, cy - y, r, g, b);
    drawPixel(cx - x, cy - y, r, g, b);
    drawPixel(cx + y, cy + x, r, g, b);
    drawPixel(cx - y, cy + x, r, g, b);
    drawPixel(cx + y, cy - x, r, g, b);
    drawPixel(cx - y, cy - x, r, g, b);
    x++;
    if (p < 0) {
      p += 2 * x + 1;
    } else {
      y--;
      p += 2 * (x - y) + 1;
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

void Renderer::translate(float x, float y, float z) const {
  glTranslatef(x, y, z);
}

void Renderer::rotate(float angle, float x, float y, float z) const {
  glRotatef(angle, x, y, z);
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