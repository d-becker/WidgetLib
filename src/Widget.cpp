#include "WidgetLib/Widget.hpp"

#include <algorithm>
#include <fstream>

#include "WidgetLib/Container.hpp"
#include "WidgetLib/evt/FocusEvent.hpp"
#include "WidgetLib/evt/KeyEvent.hpp"
#include "WidgetLib/evt/MouseEvent.hpp"
#include "WidgetLib/evt/ResizeEvent.hpp"
#include "WidgetLib/Util.hpp"
#include "WidgetLib/Toplevel.hpp"

namespace wl {

namespace /* anonymous */ {

bool file_exists(std::string filename)
{
  std::ifstream in(filename);
  return in.good();
}

// This function tries to detect the location of the font files.
// Checks for the existence of the files only once and stores
// the result in the static varuable \a res.
std::string detect_default_font_file()
{
  static std::string locations[] = {
    "/usr/share/WidgetLib/SDL_Fonts/LiberationMono-Regular.ttf",
    "/usr/local/share/WidgetLib/SDL_Fonts/LiberationMono-Regular.ttf",
    "SDL_Fonts/LiberationMono-Regular.ttf"
  };
  
  static std::string res = ""; // Stores the detected file

  if (res.empty())
  {
    for (const std::string& file : locations)
    {
      if (file_exists(file))
      {
        res = file;
	break;
      }
    }

  }

  return res;
}

} // anonymous namespace

Widget::Widget(Vec2 position,
	       int width,
	       int height)
  : m_parent(nullptr),
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
    m_canvas(nullptr),
    m_background_colour(0, 0, 0),
    m_default_font_file(detect_default_font_file()),
    m_font_file(m_default_font_file)
{
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

void Widget::addMouseObserver(std::shared_ptr<  Observer<MouseEvent> > observer)
{
  add_to_vec_uniquely(m_mouse_observers, observer);
}

void Widget::removeMouseObserver(unsigned int index)
{
  remove_from_vec(m_mouse_observers, index);
}

void Widget::removeMouseObserver(std::shared_ptr<  Observer<MouseEvent> > observer)
{
  remove_from_vec(m_mouse_observers, observer);
}

void Widget::fireMouseEvent(const MouseEvent& evt)
{
  bool handled = send_mouse_evt_to_observers(evt);
  if (!handled && m_parent) // Propagate event to parent
    m_parent->fireMouseEvent(evt);
}

void Widget::addKeyObserver(std::shared_ptr< Observer<KeyEvent> > observer)
{
  add_to_vec_uniquely(m_key_observers, observer);
}

void Widget::removeKeyObserver(unsigned int index)
{
  remove_from_vec(m_key_observers, index);
}

void Widget::removeKeyObserver(std::shared_ptr< Observer<KeyEvent> > observer)
{
  remove_from_vec(m_key_observers, observer);
}

void Widget::fireKeyEvent(const KeyEvent& evt)
{
  bool handled = send_key_evt_to_observers(evt);
  if (!handled && m_parent) // Propagate event to parent
    m_parent->fireKeyEvent(evt);
}

void Widget::addResizeObserver(std::shared_ptr< Observer<ResizeEvent> > observer)
{
  add_to_vec_uniquely(m_resize_observers, observer);
}

void Widget::removeResizeObserver(unsigned int index)
{
  remove_from_vec(m_resize_observers, index);
}

void Widget::removeResizeObserver(std::shared_ptr< Observer<ResizeEvent> > observer)
{
  remove_from_vec(m_resize_observers, observer);
}
  
void Widget::fireResizeEvent(const ResizeEvent& evt)
{
  // We never propagate the event to the parent as
  // resizing of the parent can happen separately.
  send_resize_evt_to_observers(evt);
}

void Widget::addFocusObserver(std::shared_ptr< Observer<FocusEvent> > observer)
{
  add_to_vec_uniquely(m_focus_observers, observer);
}

void Widget::removeFocusObserver(unsigned int index)
{
  remove_from_vec(m_focus_observers, index);
}

void Widget::removeFocusObserver(std::shared_ptr< Observer<FocusEvent> > observer)
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

genv::color Widget::getBackgroundColour() const
{
  return m_background_colour;
}

void Widget::setBackgroundColour(int red,
				 int green,
				 int blue)
{
  m_background_colour = genv::color(red, green, blue);
}

void Widget::setBackgroundColour(genv::color colour)
{
  m_background_colour = colour;
}

void Widget::setFont(std::string font_file)
{
  m_font_file = font_file;
  load_font();
}

// Protected
bool Widget::send_mouse_evt_to_observers(const MouseEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr< Observer<MouseEvent> > observer : m_mouse_super_observers)
  {
    if (observer)
      handled |= observer->handleEvent(evt);
  }
  
  for (std::shared_ptr< Observer<MouseEvent> > observer : m_mouse_observers)
  {
    if (observer)
      handled |= observer->handleEvent(evt);
  }

  return handled;
}

bool Widget::send_key_evt_to_observers(const KeyEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr< Observer<KeyEvent> > observer : m_key_super_observers)
  {
    if (observer)
      handled |= observer->handleEvent(evt);
  }
  
  for (std::shared_ptr< Observer<KeyEvent> > observer : m_key_observers)
  {
    if (observer)
      handled |= observer->handleEvent(evt);
  }

  return handled;
}

bool Widget::send_resize_evt_to_observers(const ResizeEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr< Observer<ResizeEvent> > observer : m_resize_super_observers)
  {
    if (observer)
      handled |= observer->handleEvent(evt);
  }
  
  for (std::shared_ptr< Observer<ResizeEvent> > observer : m_resize_observers)
  {
    if (observer)
      handled |= observer->handleEvent(evt);
  }
  
  return handled;
}

bool Widget::send_focus_evt_to_observers(const FocusEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr< Observer<FocusEvent> > observer : m_focus_super_observers)
  {
    if (observer)
      handled |= observer->handleEvent(evt);
  }
  
  for (std::shared_ptr<Observer<FocusEvent> > observer : m_focus_observers)
  {
    if (observer)
      handled |= observer->handleEvent(evt);
  }
  
  return handled;
}

void Widget::addMouseSuperObserver(std::shared_ptr< Observer<MouseEvent> > observer)
{
  add_to_vec_uniquely(m_mouse_super_observers, observer);
}

void Widget::addKeySuperObserver(std::shared_ptr< Observer<KeyEvent> > observer)
{
  add_to_vec_uniquely(m_key_super_observers, observer);
}

void Widget::addResizeSuperObserver(std::shared_ptr< Observer<ResizeEvent> > observer)
{
  add_to_vec_uniquely(m_resize_super_observers, observer);
}

void Widget::addFocusSuperObserver(std::shared_ptr< Observer<FocusEvent> > observer)
{
  add_to_vec_uniquely(m_focus_super_observers, observer);
}

void Widget::getNewCanvas()
{
  m_canvas = std::make_shared<genv::canvas>(m_width, m_height);
  load_font();
}

std::shared_ptr<genv::canvas> Widget::getCanvas()
{
  return m_canvas;
}

std::shared_ptr<const genv::canvas> Widget::getCanvas() const
{
  return m_canvas;
}

void Widget::set_parent(Container *parent)
{
  m_parent = parent;
}

void Widget::load_font()
{
  bool font_loaded = m_canvas->load_font(m_font_file, 12, false);
  if (!font_loaded)
    m_canvas->load_font(m_default_font_file, 12, false);
}

} // namespace wl
