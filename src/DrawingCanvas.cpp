#include "WidgetLib/DrawingCanvas.hpp"

namespace wl {

DrawingCanvas::DrawingCanvas(Vec2 position,
			     int height,
			     int width)
  : Widget(position, height, width)
{
}

DrawingCanvas::~DrawingCanvas()
{
}

std::shared_ptr<genv::canvas> DrawingCanvas::getCanvas()
{
  return Widget::getCanvas();
}

std::shared_ptr<const genv::canvas> DrawingCanvas::getCanvas() const
{
  return Widget::getCanvas();
}

} // namespace wl
