#include "SelectablePanel.hpp"

#include <cmath>

#include "Util.hpp"

namespace wl {

SelectablePanel::SelectablePanel(Vec2 position,
				 int width,
				 int height,
				 const std::vector<std::string>& options)
  : Container(position, width, height),
    m_elems(),
    m_selected(nullptr),
    m_first_to_display(0),
    m_elem_height(25)
{
  for (const std::string& option : options)
  {
    addOption(option);
  }
}

SelectablePanel::~SelectablePanel()
{
}

const std::vector<std::string> SelectablePanel::getOptions() const
{
  std::vector<std::string> res;
  for (const Selectable *sel : m_elems)
  {
    if (sel)
      res.emplace_back(sel->getText());
  }

  return res;
}

bool SelectablePanel::addOption(std::string option)
{
  Selectable *duplicate = find_selectable_with_text(option);
  if (duplicate)
    return false;

  // The position is not important as it will not be taken into account
  // when painting
  Selectable *new_elem = new Selectable(Vec2(0, 0), getWidth(),
					m_elem_height, option);

  bool added = addChild(new_elem);
  if (added)
    return true;
  else
  {
    delete new_elem;
    return false;
  }
}

bool SelectablePanel::removeOption(const std::string& option)
{
  Selectable *elem = find_selectable_with_text(option);
  if (elem)
  {
    remove_from_vec(m_elems, elem);
    delete elem;
    return true;
  }

  return false;
}

const std::string& SelectablePanel::getSelected() const
{
  static const std::string empty_string = "";
  if (m_selected)
    return m_selected->getText();
  else
    return empty_string;
}

bool SelectablePanel::setSelected(const std::string& option)
{
  Selectable *to_select = find_selectable_with_text(option);
  if (to_select)
  {
    // Deselecting the previously selected element
    if (m_selected)
      m_selected->deselect();

    // Selecting the new one
    m_selected = to_select;
    m_selected->select();

    return true;
  }

  return false;
}

Widget* SelectablePanel::getWidgetAtPos(const Vec2& pos)
{
  int index_of_elem = pos.x / m_elem_height;
  return m_elems.at(index_of_elem);
}

void SelectablePanel::layOutChildren()
{
  int sum_height = 0; 
  for (Widget *child : getChildren())
  {
    if (child)
    {
      child->setPosition(0, sum_height);
      sum_height += m_elem_height;
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
      current_y += m_elem_height;
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
