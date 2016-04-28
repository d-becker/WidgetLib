#include "Widget.hpp"

#include <algorithm>

#include "Container.hpp"
#include "Util.hpp"
#include "Toplevel.hpp"

namespace wl {

Widget::Widget(Vec2 position,
	       int width,
	       int height)
  : m_parent(nullptr),
    m_position(position),
    m_width(width),
    m_height(height),
    m_canvas(nullptr),
    m_background_colour(0, 0, 0)
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

// Protected
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

void Widget::set_parent(Container *parent)
{
  m_parent = parent;
}

} // namespace wl
