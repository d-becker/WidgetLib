#include "Container.hpp"

namespace wl {

Container::Container(Vec2 position = Vec2(0, 0),
		     int width = 0,
		     int height = 0)
  : m_parent(parent),
    m_position(position),
    m_width(width),
    m_height(height)
{
}

Container::~Container()
{
}

const std::vector<Widget>& Container::getChildren() const
{
  return m_children;
}

std::shared_ptr<Widget> Container::getWidgetAtPos(const Vec2& pos)
{
  for (std::shared_ptr<Widget> child : m_children)
  {
    if (child && child->isInside(pos))
    {
      return child->getWidgetAtPos(pos - child->getPosition());
    }
  }

  return nullptr;
}

} // namespace wl
