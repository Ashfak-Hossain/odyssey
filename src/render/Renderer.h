#ifndef RENDERER_H
#define RENDERER_H

#include <string>

/**
 * @brief OpenGL helper.
 * Every other renderer use there instead of using glut function everywhere.
 */
class Renderer {
 public:
  /**
   * @brief Clears color buffer (glClear(GL_COLOR_BUFFER_BIT)).
   * - fills pixels with background color from glClearColor() @ref Game::init().
   */
  void clearScreen() const;
  void swapBuffers() const;

  void enableBlending() const;
  void disableBlending() const;

  void pushMatrix() const;
  void popMatrix() const;

  // load identity matrix before any matrix transformation
  void loadIdentity() const;

  void translate(float x, float y) const;                     // 2D
  void translate(float x, float y, float z) const;            // 3D
  void rotate(float angle, float x, float y, float z) const;  // 3D

  /**
   * @brief draw a point with (r, g, b)
   * x, y - point
   */
  void drawPixel(float x, float y, float r, float g, float b) const;

  /**
   * @brief draw line with mid point line algorithm
   *  x, y - point
   * r, g, b - color
   */
  void drawMidpointLine(int x0, int y0, int x1, int y1, float r, float g, float b) const;

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

  /**
   * @brief Draws a full-screen black fade overlay.
   * alpha = 0 is invisible, 1 is fully black.
   */
  void drawTransition(float alpha, float screenW, float screenH) const;
};

#endif  // RENDERER_H