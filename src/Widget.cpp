#include "Widget.hpp"
#include "Container.hpp"

namespace wl {

Vec2 Widget::getAbsPosition() const
{
  if (m_parent)
    return m_parent->getAbsPosition() + m_position;
  else
    return m_position;
}

} // namespace wl
