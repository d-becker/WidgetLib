#include "Container.hpp"

#include <algorithm>

namespace wl {

Container::Container(Container *parent,
		     Vec2 position,
		     int width,
		     int height)
  : Widget(parent, position, width, height)
{
}

Container::~Container()
{
  for (Widget *child : m_children)
  {
    delete child;
    child = nullptr;
  }
}

bool Container::addChild(Widget *child)
{
  if (!child || child->getParent() != this
      || std::find(m_children.begin(), m_children.end(), child)
                                           != m_children.end())
    return false;

  m_children.emplace_back(child);
  return true;
}

bool Container::removeChild(Widget *child)
{
  auto it = std::find(m_children.begin(), m_children.end(), child);
  if (it != m_children.end())
  {
    m_children.erase(it);
    return true;
  }

  return false;
}

const std::vector<Widget*>& Container::getChildren() const
{
  return m_children;
}

Widget *Container::getWidgetAtPos(const Vec2& pos)
{
  for (Widget *child : m_children)
  {
    if (child && child->isInside(pos))
    {
      return child->getWidgetAtPos(pos - child->getPosition());
    }
  }

  return this;
}

} // namespace wl
