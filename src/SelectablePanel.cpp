#include "SelectablePanel.hpp"

#include <cmath>

#include "Util.hpp"

namespace wl {

SelectablePanel::SelectablePanel(Vec2 position,
				 int width,
				 int height,
				 const std::vector<Selectable*>& elems)
  : Container(position, width, height),
    m_elems()
{
  for (Selectable *elem : elems)
  {
    add_elem_without_resize(elem);
  }

  adjust_size();
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
  bool added = add_elem_without_resize(elem);
  adjust_size();
  return added;
}

bool SelectablePanel::removeElement(Selectable *elem)
{
  bool removed = removeChild(elem);
  if (removed)
  {
    remove_from_vec(m_elems, elem);
    if (elem) // Adjusting size
    {
      int new_height = getHeight() - elem->getHeight();
      int new_width = get_max_child_width();
      setSize(new_width, new_height);
    }
  }

  return removed;
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

// Private
bool SelectablePanel::add_elem_without_resize(Selectable *elem)
{
  bool added = addChild(elem);
  if (added)
    m_elems.emplace_back(elem);

  return added;
}

void SelectablePanel::adjust_size()
{
  // TODO.
  int new_width;
  int new_height;
  get_new_size(new_width, new_height);
  setSize(new_width, new_height);
}

void SelectablePanel::get_new_size(int& new_width, int& new_height) const
{
  int max_width = 0;
  int sum_height = 0;
  for (const Widget *child : getChildren())
  {
    if (child)
    {
      int child_width = child->getWidth();
      if (child_width > max_width)
        max_width = child_width;

      sum_height += child->getHeight();
    }
  }

  new_width = max_width;
  new_height = sum_height;
}

int SelectablePanel::get_max_child_width() const
{
  int max_width = 0;

  for (const Widget *child : getChildren())
  {
    if (child)
    {
      int new_max_width = child->getWidth();
      if (new_max_width > max_width)
	max_width = new_max_width;
    }
  }

  return max_width;
}

int SelectablePanel::get_sum_child_height() const
{
  int sum_height = 0;

  for (const Widget *child : getChildren())
  {
    if (child)
    {
      sum_height += child->getHeight();
    }
  }

  return sum_height;
}

} // namespace wl
