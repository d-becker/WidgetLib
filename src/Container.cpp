#include "Container.hpp"

#include <algorithm>

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

bool Container::addChild(std::shared_ptr<Widget> child)
{
  if (!child || child->getParent() != this
      || std::find(m_children.begin(), m_children.end(), child)
                                           != m_children.end())
    return false;

  m_children.emplace_back(child);
  return true;
}

bool Container::removeChild(std::shared_ptr<Widget> child)
{
  auto it = std::find(m_children.begin(), m_children.end(), child);
  if (it != m_children.end())
  {
    m_children.erase(it);
    return true;
  }

  return false;
}

const std::vector<Widget>& Container::getChildren() const
{
  return m_children;
}

Widget* Container::getWidgetAtPos(const Vec2& pos)
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
