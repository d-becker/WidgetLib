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

} // namespace wl
