#include "Button.hpp"

#include <graphics.hpp>

namespace wl {

Button::Button(Container *parent,
	       Vec2 position,
	       int width,
	       int height
	       )
  : Widget(parent, position, width, height)
{
}

Button::~Button()
{
}

void Button::paint() const
{
  // Testing
  using namespace genv;
  Vec2 pos = getAbsPosition();
  gout << move_to(pos.x, pos.y);
  gout << color(0, 0, 255);
  gout << box(getWidth(), getHeight());
}

} // namespace wl
