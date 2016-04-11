#include "Widget.hpp"
#include "Container.hpp"

namespace wl {

Widget::Widget(Container *parent,
	       Vec2 position,
	       int width,
	       int height)
  : m_parent(parent),
    m_position(position),
    m_width(width),
    m_height(height)
{
  if (m_parent)
  {
    parent->addChild(this);
  }
}

Vec2 Widget::getAbsPosition() const
{
  if (m_parent)
    return m_parent->getAbsPosition() + m_position;
  else
    return m_position;
}

} // namespace wl
