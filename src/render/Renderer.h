#ifndef RENDERER_H
#define RENDERER_H

#include <string>

/**
 * @brief OpenGL helper.
 * Every other renderer use there instead of using glut function everywhere.
 */
class Renderer {
 public:
  void clearScreen() const;
  void swapBuffers() const;

  void enableBlending() const;
  void disableBlending() const;

  void pushMatrix() const;
  void popMatrix() const;
  void loadIdentity() const;
  void translate(float x, float y) const;

  /**
   * @brief draw a quad filled with (r, g, b) color.
   * x, y - bottom-lect corner of the box
   * w, h - height and width of the box
   */
  void drawQuad(float x, float y, float w, float h, float r, float g, float b) const;

  /**
   * @brief draw a quad filled with alpha (r, g, b, a) color.
   * x, y - bottom-lect corner of the box
   * w, h - height and width of the box
   */
  void drawQuadAlpha(float x, float y, float w, float h, float r, float g, float b, float a) const;

  /**
   * @brief draw a quad outline with (r, g, b) color.
   * x, y - bottom-lect corner of the box
   * w, h - height and width of the box
   * default line width - 1.0f
   */
  void drawQuadOutline(
      float x, float y, float w, float h, float r, float g, float b, float lineWidth = 1.0f) const;

  /**
   * @brief Draw a triangle filled with (r, g, b) color
   */
  void drawTriangle(
      float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) const;

  /**
   * @brief Draw a bitmap string at world position (x, y).
   */
  void drawText(float x, float y, const std::string& text, float r, float g, float b) const;
};

#endif  // RENDERER_H