#include "Container.hpp"

#include <algorithm>

namespace wl {

Container::Container(Container *parent,
		     Vec2 position,
		     int width,
		     int height,
		     std::shared_ptr<LayoutManager> layout_manager)
  : Widget(parent, position, width, height),
    m_layout_manager(layout_manager),
    m_background_colour(0, 0, 0)
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

genv::color Container::getBackgroundColour() const
{
  return m_background_colour;
}

void Container::setBackgroundColour(int red,
				    int green,
				    int blue)
{
  m_background_colour = genv::color(red, green, blue);
}

void Container::setBackgroundColour(genv::color colour)
{
  m_background_colour = colour;
}

std::shared_ptr<LayoutManager> Container::getLayoutManager() const
{
  return m_layout_manager;
}

void Container::setLayoutManager(std::shared_ptr<LayoutManager> layout_manager)
{
  m_layout_manager = layout_manager;
}

void Container::layOutChildren()
{
  if (m_layout_manager)
    m_layout_manager->layOutContainer(*this);
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

void Container::paint()
{
  using namespace genv;
  std::shared_ptr<canvas> my_canvas_ptr = getCanvas();
  if (!my_canvas_ptr)
    return;

  canvas& my_canvas = *my_canvas_ptr;
  
  // Wiping with background colour
  my_canvas << move_to(0, 0);
  my_canvas << m_background_colour;
  my_canvas << box(getWidth(), getHeight());

  for (Widget* child : m_children)
  {
    if (child)
    {
      child->paint();
      Vec2 child_pos = child->getPosition();
      child->stampCanvas(my_canvas, child_pos.x, child_pos.y);
    }
  }
}

} // namespace wl
