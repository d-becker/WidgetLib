#include "SelectablePanel.hpp"

#include <cmath>

#include "Util.hpp"

namespace wl {

SelectablePanel::SelectablePanel(Vec2 position,
				 int width,
				 int height,
				 const std::vector<Selectable*>& elems)
  : Container(position, width, height),
    m_elems(),
    m_first_to_display(0)
{
  for (Selectable *elem : elems)
  {
    addElement(elem);
  }
}

SelectablePanel::~SelectablePanel()
{
}

const std::vector<Selectable*> SelectablePanel::getElements() const
{
  return m_elems;
}

bool SelectablePanel::addElement(Selectable *elem)
{
  bool added = addChild(elem);
  if (added)
    m_elems.emplace_back(elem);

  return added;
}

bool SelectablePanel::removeElement(Selectable *elem)
{
  bool removed = removeChild(elem);
  if (removed)
  {
    remove_from_vec(m_elems, elem);
  }

  return removed;
}

bool SelectablePanel::removeElementByText(std::string text)
{
  Selectable *elem = find_selectable_with_text(text);
  return removeElement(elem);
}

void SelectablePanel::layOutChildren()
{
  int sum_height = 0; 
  for (Widget *child : getChildren())
  {
    if (child)
    {
      child->setPosition(0, sum_height);
      sum_height += child->getHeight();
    }
  }
}

void SelectablePanel::paint()
{
  // TODO.
  using namespace genv;
  std::shared_ptr<canvas> my_canvas_ptr = getCanvas();
  if (!my_canvas_ptr)
    return;

  canvas& my_canvas = *my_canvas_ptr;

  int my_height = getHeight();
  
  // Wiping with background colour
  my_canvas << move_to(0, 0);
  my_canvas << getBackgroundColour();
  my_canvas << box(getWidth(), my_height);

  // Painting the children
  const std::vector<Widget*> children = getChildren();
  int current_y = 0;
  for (unsigned int i = m_first_to_display;
       i < children.size() && current_y < my_height;
       ++i)
  {
    Widget *child = children.at(i);
    if (child)
    {
      child->paint();
      child->stampCanvas(my_canvas, 0, current_y);
      current_y += child->getHeight();
    }
  }
}

// Private
Selectable *SelectablePanel::find_selectable_with_text(const std::string& text)
{
  for (Selectable *sel : m_elems)
  {
    if (sel && sel->getText() == text)
      return sel;
  }

  return nullptr;
}

} // namespace wl
