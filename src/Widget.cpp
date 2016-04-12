#include "Widget.hpp"

#include <algorithm>

#include "Container.hpp"

namespace wl {

Widget::Widget(Container *parent,
	       Vec2 position,
	       int width,
	       int height)
  : m_parent(parent),
    m_position(position),
    m_width(width),
    m_height(height),
    m_mouse_observers()
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

void Widget::addMouseObserver(std::shared_ptr<MouseObserver> observer)
{
  if (std::find(m_mouse_observers.begin(), m_mouse_observers.end(), observer)
                                                 == m_mouse_observers.end())
    m_mouse_observers.emplace_back(observer);
}

void Widget::removeMouseObserver(unsigned int index)
{
  auto it = m_mouse_observers.begin() + index;
  if (it < m_mouse_observers.end())
    m_mouse_observers.erase(it);
}

void Widget::removeMouseObserver(std::shared_ptr<MouseObserver> observer)
{
  auto it = std::find(m_mouse_observers.begin(),
		      m_mouse_observers.end(),
		      observer);
  if (it < m_mouse_observers.end())
    m_mouse_observers.erase(it);
}

void Widget::fireMouseEvent(const MouseEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr<MouseObserver> observer : m_mouse_observers)
  {
    if (observer)
      handled |= observer->handleMouseEvent(evt);
  }

  if (!handled && m_parent)
    m_parent->fireMouseEvent(evt);
}

} // namespace wl
