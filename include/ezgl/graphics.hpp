#ifndef EZGL_GRAPHICS_HPP
#define EZGL_GRAPHICS_HPP

#include <ezgl/colour.hpp>
#include <ezgl/point.hpp>
#include <ezgl/rectangle.hpp>

#include <cairo.h>

#include <string>
#include <vector>

namespace ezgl {

class camera;

/**
 * The slant of the font.
 *
 * This enum is setup to match with the cairo graphics library and should not be changed.
 */
enum class font_slant : int {
  /**
   * No slant.
   */
  normal = CAIRO_FONT_SLANT_NORMAL,

  /**
   * Slant is more calligraphic. Make sure the font you're using has an italic design, otherwise it may look ugly.
   */
  italic = CAIRO_FONT_SLANT_ITALIC,

  /**
   * Slanted to the right.
   */
  oblique = CAIRO_FONT_SLANT_OBLIQUE
};

/**
 * The weight of the font.
 */
enum class font_weight : int {
  /**
   * No additional weight.
   */
  normal = CAIRO_FONT_WEIGHT_NORMAL,

  /**
   * Bold font weight.
   */
  bold = CAIRO_FONT_WEIGHT_BOLD
};

/**
 * The shape of a line's start and end point.
 */
enum class line_cap : int {
  /**
   * Start and stop the line exactly where it begins/ends.
   */
  butt = CAIRO_LINE_CAP_BUTT,

  /**
   * Each end of the line has circles.
   */
  round = CAIRO_LINE_CAP_ROUND,

  /**
   * Each end of the line has squares.
   */
  square = CAIRO_LINE_CAP_SQUARE
};

/**
 * The dash style of a line.
 */
enum class line_dash : int {
  /**
   * No dashes in the line (i.e., solid).
   */
  none,

  /**
   * Dash to whitespace ratio is 5:3.
   */
  asymmetric_5_3
};

/**
 * A thin wrapper around a cairo graphics state.
 */
class graphics {
public:
  /**
   * Constructor.
   *
   * @param cairo The cairo graphics state.
   */
  graphics(cairo_t *cairo, camera *cam);

  /**
   * Change the colour for subsequent draw calls.
   *
   * @param new_colour The new colour to use.
   */
  void set_colour(colour new_colour);

  /**
   * Change the colour for subsequent draw calls.
   *
   * @param red The amount of red to use, between 0 and 255.
   * @param green The amount of green to use, between 0 and 255.
   * @param blue The amount of blue to use, between 0 and 255.
   * @param alpha The transparency level (0 is fully transparent, 255 is opaque).
   */
  void
  set_colour(uint_fast8_t red, uint_fast8_t green, uint_fast8_t blue, uint_fast8_t alpha = 255);

  /**
   * Change how line endpoints will be rendered in subsequent draw calls.
   */
  void set_line_cap(line_cap cap);

  /**
   * Change the dash style of the line.
   */
  void set_line_dash(line_dash dash);

  /**
   * Set the line width.
   *
   * @param width The width in pixels. A value of 0 means as thin as possible.
   */
  void set_line_width(int width);

  /**
   * Change the font size.
   *
   * @param new_size The new size text should be drawn at.
   */
  void set_font_size(double new_size);

  /**
   * Change the font.
   *
   * @param family The font family to use (e.g., serif)
   * @param slant The slant to use (e.g., italic)
   * @param weight The weight of the font (e.g., bold)
   */
  void format_font(std::string const &family, font_slant slant, font_weight weight);

  /**
   * Change the font.
   *
   * @param family The font family to use (e.g., serif)
   * @param slant The slant to use (e.g., italic)
   * @param weight The weight of the font (e.g., bold)
   * @param new_size The new size text should be drawn at.
   */
  void
  format_font(std::string const &family, font_slant slant, font_weight weight, double new_size);

  /**
   * Draw a line.
   *
   * @param start The start point of the line, in pixels.
   * @param end The end point of the line, in pixels.
   */
  void draw_line(point2d start, point2d end);

  /**
   * Draw the outline a rectangle.
   *
   * @param start The start point of the rectangle, in pixels.
   * @param end The end point of the rectangle, in pixels.
   */
  void draw_rectangle(point2d start, point2d end);

  /**
   * Draw the outline of a rectangle.
   *
   * @param start The start point of the rectangle, in pixels.
   * @param width How wide the rectangle is, in pixels.
   * @param height How high the rectangle is, in pixels.
   */
  void draw_rectangle(point2d start, double width, double height);

  /**
   * Draw the outline of a rectangle.
   */
  void draw_rectangle(rectangle const &r);

  /**
   * Draw a filled in rectangle.
   *
   * @param start The start point of the rectangle, in pixels.
   * @param end The end point of the rectangle, in pixels.
   */
  void fill_rectangle(point2d start, point2d end);

  /**
   * Draw a filled in rectangle.
   *
   * @param start The start point of the rectangle, in pixels.
   * @param width How wide the rectangle is, in pixels.
   * @param height How high the rectangle is, in pixels.
   */
  void fill_rectangle(point2d start, double width, double height);

  /**
   * Draw a filled in rectangle.
   */
  void fill_rectangle(rectangle const &r);

  /**
   * Draw a filled polygon.
   *
   * @param points The points to draw. The first and last points are connected to close the polygon.
   */
  void fill_poly(std::vector<point2d> const &points);

  /**
   * Draw text centred around a point.
   *
   * @param centre The centre of the text, in pixels.
   * @param text The text to draw.
   */
  void draw_text(point2d centre, std::string const &text);

private:
  void draw_rectangle_path(point2d start, point2d end);

  // A non-owning pointer to a cairo graphics context.
  cairo_t *m_cairo;

  // A non-owning pointer to the camera.
  camera *m_camera;
};
}

#endif //EZGL_GRAPHICS_HPP
