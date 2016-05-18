#include "Container.hpp"

#include <algorithm>

#include "evt/ObserverAdapter.hpp"
#include "evt/ResizeEvent.hpp"

namespace wl {

Container::Container(Vec2 position,
		     int width,
		     int height)
  : Widget(position, width, height)
{
  // Lay out children on resize
  addResizeSuperObserver(std::make_shared< ObserverAdapter<ResizeEvent> >(
					  [this](const ResizeEvent& evt) {
	layOutChildren();
	return true;
      }));
}

Container::~Container()
{
  for (Widget *child : m_children)
  {
    delete child;
    child = nullptr;
  }
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

// Protected
bool Container::addChild(Widget *child)
{
  if (!child || child->getParent() != nullptr
      || std::find(m_children.begin(), m_children.end(), child)
                                           != m_children.end())
    return false;

  m_children.emplace_back(child);
  child->set_parent(this);
  return true;
}

bool Container::removeChild(Widget *child)
{
  auto it = std::find(m_children.begin(), m_children.end(), child);
  if (it != m_children.end())
  {
    m_children.erase(it);
    child->set_parent(nullptr);
    return true;
  }

  return false;
}

} // namespace wl
