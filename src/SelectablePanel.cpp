#include "SelectablePanel.hpp"

#include <cmath>

#include "MouseEvent.hpp"
#include "ObserverAdapter.hpp"
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
  // Setting the background colour
  setBackgroundColour(255, 255, 255); // white
  
  // Creating and adding the children
  for (const std::string& option : options)
  {
    addOption(option);
  }

  // Mouse observer
  addMouseSuperObserver(std::make_shared< ObserverAdapter<MouseEvent> >([this](const MouseEvent& evt) {
	auto evt_type = evt.getEvtType();
	if (evt_type == MouseEvent::MOUSE_WHEEL_UP)
	{
	  scrollUp();
	  return true;
	}
	else if (evt_type == MouseEvent::MOUSE_WHEEL_DOWN)
	{
	  scrollDown();
	  return true;
	}

	return false;
      }));
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
  {
    m_elems.emplace_back(new_elem);
    
    // Mouse observer
    new_elem->addMouseObserver(
	       std::make_shared< ObserverAdapter<MouseEvent> >(
	       [this, new_elem](const MouseEvent& evt)
	       {
		 if (evt.getEvtType() == MouseEvent::CLICKED_ON_WIDGET)
		 {
		   select_selectable(new_elem);
		   return true;
		 }
		 else
		 {
		   return false;
		 }
	       }));
    
    return true;
  }
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
  bool selected = select_selectable(to_select);

  if (selected)
  {
    SelectionGroupEvent evt(this, option);
    fireEvent(evt);
  }

  return selected;
}

void SelectablePanel::clearSelection()
{
  // Deselecting the previously selected element
  if (m_selected)
    m_selected->deselect();

  // Nulling m_selected
  m_selected = nullptr;
}

void SelectablePanel::scrollUp()
{
  if (m_first_to_display > 0)
    --m_first_to_display;
}

void SelectablePanel::scrollDown()
{
  if (m_first_to_display < m_elems.size() - getHeight() /  m_elem_height)
    ++m_first_to_display;
}

Widget* SelectablePanel::getWidgetAtPos(const Vec2& pos)
{
  unsigned int index_of_elem = pos.y / m_elem_height + m_first_to_display;
  const std::vector<Widget*>& children = getChildren();
  
  if (index_of_elem >= 0 && index_of_elem < children.size())
    return getChildren().at(index_of_elem);
  else
    return this;
}

void SelectablePanel::layOutChildren()
{
  // Only the size needs to be adjusted as the positions
  // are not taken into account when painting.
  int width = getWidth();
  for (Selectable *elem : m_elems)
  {
    if (elem)
      elem->setSize(m_elem_height, width);
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
  int current_y = 0;
  for (unsigned int i = m_first_to_display;
       i < m_elems.size() && current_y < my_height;
       ++i)
  {
    Selectable *elem = m_elems.at(i);
    if (elem)
    {
      elem->paint();
      elem->stampCanvas(my_canvas, 0, current_y);
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

bool SelectablePanel::select_selectable(Selectable *to_select)
{
  if (to_select && vec_contains(m_elems, to_select))
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

} // namespace wl
