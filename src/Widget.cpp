#include "Widget.hpp"

#include <algorithm>

#include "Container.hpp"
#include "KeyEvent.hpp"
#include "KeyObserver.hpp"
#include "MouseEvent.hpp"
#include "MouseObserver.hpp"

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

Toplevel *Widget::getToplevel()
{
  if (m_parent)
    return m_parent->getToplevel();
  else
    return nullptr;
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

  if (!handled && m_parent) // Propagate event to parent
    m_parent->fireMouseEvent(evt);
}

void Widget::addKeyObserver(std::shared_ptr<KeyObserver> observer)
{
  if (std::find(m_key_observers.begin(), m_key_observers.end(), observer)
      == m_key_observers.end())
    m_key_observers.emplace_back(observer);
}

void Widget::removeKeyObserver(unsigned int index)
{
  auto it = m_key_observers.begin() + index;
  if (it < m_key_observers.end())
    m_key_observers.erase(it);
}

void Widget::removeKeyObserver(std::shared_ptr<KeyObserver> observer)
{
  auto it = std::find(m_key_observers.begin(),
		      m_key_observers.end(),
		      observer);
  if (it < m_key_observers.end())
    m_key_observers.erase(it);
}
  
/**
 * If a key event happens over this widget, the \c Toplevel that created
 * the event communicates it to the widget with this method. This method then
 * notifies all the observers that are subscribed to this event.
 *
 * \param evt The event to fire.
 */
void Widget::fireKeyEvent(const KeyEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr<KeyObserver> observer : m_key_observers)
  {
    if (observer)
      handled |= observer->handleKeyEvent(evt);
  }

  if (!handled && m_parent) // Propagate event to parent
    m_parent->fireKeyEvent(evt);
}

} // namespace wl
