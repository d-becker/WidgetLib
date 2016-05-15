#ifndef DRAWING_CANVAS_HPP
#define DRAWING_CANVAS_HPP

#include "Widget.hpp"

namespace wl {


/**
 * A class that allows free drawing. This class provides a public \c getCanvas
 * method which can be used to access the underlying genv::canvas to draw on it.
 */
class DrawingCanvas : public Widget
{
public:
  DrawingCanvas(Vec2 position,
		int width,
		int height);

  virtual ~DrawingCanvas();

  /**
   * Returns the canvas associated with this widget.
   */
  std::shared_ptr<genv::canvas> getCanvas();

  /**
   * Const version of the above.
   */
  std::shared_ptr<const genv::canvas> getCanvas() const;
};

} // namespace wl

#endif // DRAWING_CANVAS_HPP
