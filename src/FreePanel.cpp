#include "WidgetLib/FreePanel.hpp"

namespace wl {

FreePanel::FreePanel(Vec2 position,
		     int width,
		     int height)
  : Container(position, width, height)
{
}

FreePanel::~FreePanel()
{
}

bool FreePanel::addChild(Widget *child)
{
  return Container::addChild(child);
}

bool FreePanel::removeChild(Widget *child)
{
  return Container::removeChild(child);
}

void FreePanel::layOutChildren()
{
}

} // namespace wl
