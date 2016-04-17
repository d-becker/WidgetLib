#include "Widget.hpp"

#include <algorithm>

#include "Container.hpp"
#include "FocusEvent.hpp"
#include "FocusObserver.hpp"
#include "KeyEvent.hpp"
#include "KeyObserver.hpp"
#include "MouseEvent.hpp"
#include "MouseObserver.hpp"
#include "ResizeEvent.hpp"
#include "ResizeObserver.hpp"
#include "Toplevel.hpp"

namespace wl {

namespace { // Anonymous namespace

template <typename T>
bool vec_contains(const std::vector<T>& vec, T elem)
{
  return std::find(vec.begin(), vec.end(), elem) != vec.end();
}

template <typename T>
void add_to_vec_uniquely(std::vector<T>& vec, T elem)
{
  if (!vec_contains(vec, elem))
    vec.emplace_back(elem);
}

template <typename T>
void remove_from_vec(std::vector<T>& vec, unsigned int index)
{
  auto it =vec.begin() + index;
  if (it < vec.end())
    vec.erase(it);
}

template <typename T>
void remove_from_vec(std::vector<T>& vec, T elem)
{
  auto it = std::find(vec.begin(), vec.end(), elem);
  if (it < vec.end())
    vec.erase(it);
}

} // anonymous namespace

Widget::Widget(Container *parent,
	       Vec2 position,
	       int width,
	       int height)
  : m_parent(parent),
    m_position(position),
    m_width(width),
    m_height(height),
    m_mouse_observers(),
    m_key_observers(),
    m_resize_observers(),
    m_focus_observers(),
    m_mouse_super_observers(),
    m_key_super_observers(),
    m_resize_super_observers(),
    m_focus_super_observers(),
    m_canvas(nullptr)
{
  if (m_parent)
  {
    parent->addChild(this);
  }

  getNewCanvas();
}

Widget::~Widget()
{
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
  add_to_vec_uniquely(m_mouse_observers, observer);
}

void Widget::removeMouseObserver(unsigned int index)
{
  remove_from_vec(m_mouse_observers, index);
}

void Widget::removeMouseObserver(std::shared_ptr<MouseObserver> observer)
{
  remove_from_vec(m_mouse_observers, observer);
}

void Widget::fireMouseEvent(const MouseEvent& evt)
{
  bool handled = send_mouse_evt_to_observers(evt);
  if (!handled && m_parent) // Propagate event to parent
    m_parent->fireMouseEvent(evt);
}

void Widget::addKeyObserver(std::shared_ptr<KeyObserver> observer)
{
  add_to_vec_uniquely(m_key_observers, observer);
}

void Widget::removeKeyObserver(unsigned int index)
{
  remove_from_vec(m_key_observers, index);
}

void Widget::removeKeyObserver(std::shared_ptr<KeyObserver> observer)
{
  remove_from_vec(m_key_observers, observer);
}

void Widget::fireKeyEvent(const KeyEvent& evt)
{
  bool handled = send_key_evt_to_observers(evt);
  if (!handled && m_parent) // Propagate event to parent
    m_parent->fireKeyEvent(evt);
}

void Widget::addResizeObserver(std::shared_ptr<ResizeObserver> observer)
{
  add_to_vec_uniquely(m_resize_observers, observer);
}

void Widget::removeResizeObserver(unsigned int index)
{
  remove_from_vec(m_resize_observers, index);
}

void Widget::removeResizeObserver(std::shared_ptr<ResizeObserver> observer)
{
  remove_from_vec(m_resize_observers, observer);
}
  
void Widget::fireResizeEvent(const ResizeEvent& evt)
{
  // We never propagate the event to the parent as
  // resizing of the parent can happen separately.
  send_resize_evt_to_observers(evt);
}

void Widget::addFocusObserver(std::shared_ptr<FocusObserver> observer)
{
  add_to_vec_uniquely(m_focus_observers, observer);
}

void Widget::removeFocusObserver(unsigned int index)
{
  remove_from_vec(m_focus_observers, index);
}

void Widget::removeFocusObserver(std::shared_ptr<FocusObserver> observer)
{
  remove_from_vec(m_focus_observers, observer);
}

void Widget::fireFocusEvent(const FocusEvent& evt)
{
  bool handled = send_focus_evt_to_observers(evt);
  if (!handled && m_parent) // Propagate event to parent
    m_parent->fireFocusEvent(evt);
}

void Widget::grabFocus()
{
  Toplevel *tl = getToplevel();
  if (tl)
    tl->setFocussed(this);
}

// Protected
bool Widget::send_mouse_evt_to_observers(const MouseEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr<MouseObserver> observer : m_mouse_super_observers)
  {
    if (observer)
      handled |= observer->handleMouseEvent(evt);
  }
  
  for (std::shared_ptr<MouseObserver> observer : m_mouse_observers)
  {
    if (observer)
      handled |= observer->handleMouseEvent(evt);
  }

  return handled;
}

bool Widget::send_key_evt_to_observers(const KeyEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr<KeyObserver> observer : m_key_super_observers)
  {
    if (observer)
      handled |= observer->handleKeyEvent(evt);
  }
  
  for (std::shared_ptr<KeyObserver> observer : m_key_observers)
  {
    if (observer)
      handled |= observer->handleKeyEvent(evt);
  }

  return handled;
}

bool Widget::send_resize_evt_to_observers(const ResizeEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr<ResizeObserver> observer : m_resize_super_observers)
  {
    if (observer)
      handled |= observer->handleResizeEvent(evt);
  }
  
  for (std::shared_ptr<ResizeObserver> observer : m_resize_observers)
  {
    if (observer)
      handled |= observer->handleResizeEvent(evt);
  }
  
  return handled;
}

bool Widget::send_focus_evt_to_observers(const FocusEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr<FocusObserver> observer : m_focus_super_observers)
  {
    if (observer)
      handled |= observer->handleFocusEvent(evt);
  }
  
  for (std::shared_ptr<FocusObserver> observer : m_focus_observers)
  {
    if (observer)
      handled |= observer->handleFocusEvent(evt);
  }
  
  return handled;
}

void Widget::addMouseSuperObserver(std::shared_ptr<MouseObserver> observer)
{
  add_to_vec_uniquely(m_mouse_super_observers, observer);
}

void Widget::addKeySuperObserver(std::shared_ptr<KeyObserver> observer)
{
  add_to_vec_uniquely(m_key_super_observers, observer);
}

void Widget::addResizeSuperObserver(std::shared_ptr<ResizeObserver> observer)
{
  add_to_vec_uniquely(m_resize_super_observers, observer);
}

void Widget::addFocusSuperObserver(std::shared_ptr<FocusObserver> observer)
{
  add_to_vec_uniquely(m_focus_super_observers, observer);
}

void Widget::getNewCanvas()
{
  m_canvas = std::make_shared<genv::canvas>(m_width, m_height);
  m_canvas->load_font("Fonts/LiberationMono-Regular.ttf", 12, false);
}

std::shared_ptr<genv::canvas> Widget::getCanvas()
{
  return m_canvas;
}

std::shared_ptr<const genv::canvas> Widget::getCanvas() const
{
  return m_canvas;
}

} // namespace wl
