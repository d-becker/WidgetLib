#include "SelectionGroup.hpp"

#include <memory>
#include <vector>

#include "SelectionGroupEvent.hpp"
#include "ObserverAdapter.hpp"
#include "Util.hpp"

namespace wl {

SelectionGroup::SelectionGroup(Vec2 position,
			       int width,
			       int height,
			       const std::vector<std::string>& options)
  : Container(position, width, height),
    m_panel(nullptr),
    m_selected(nullptr)
{
  std::vector<Selectable*> selectables;
  for (const std::string option : options)
  {
    Selectable *selectable = new Selectable(Vec2(0, 0), width, 30, option);
    selectable->addObserver(std::make_shared< ObserverAdapter<SelectionEvent> >(
					      get_observer_lambda(selectable)));
    selectables.emplace_back(selectable);
  }

  m_panel = new SelectablePanel(Vec2(0, 0), width, height, selectables);

  addChild(m_panel);
}

SelectionGroup::~SelectionGroup()
{
}

std::vector<std::string> SelectionGroup::getOptions() const
{
  std::vector<std::string> res;
  for (const Selectable * sel : m_panel->getElements())
  {
    if (sel)
      res.emplace_back(sel->getText());
  }

  return res;
}

bool SelectionGroup::addOption(std::string option)
{
  if (!vec_contains(getOptions(), option))
  {
    Selectable *selectable = new Selectable(Vec2(0, 0), getWidth(), 30, option);
    selectable->addObserver(std::make_shared< ObserverAdapter<SelectionEvent> >(
					    get_observer_lambda(selectable)));
    return m_panel->addElement(selectable);
  }

  return false;
}

bool SelectionGroup::removeOption(std::string option)
{
  return m_panel->removeElementByText(option);
}

std::string SelectionGroup::getSelected() const
{
  return m_selected;
}

bool SelectionGroup::setSelected(const std::string& option)
{
}

void SelectionGroup::clearSelection()
{
}

void SelectionGroup::layOutChildren()
{
  // TODO
}

// Private
std::function<bool(const SelectionEvent&)>
SelectionGroup::get_observer_lambda(Selectable *selectable)
{
  auto res = [this, selectable](const SelectionEvent& evt) {
    if (evt.getEvtType() == SelectionEvent::SELECTION_SET)
    {
      // Deselecting the previously selected \c Selectable
      if (m_selected)
	m_selected->deselect();

      // Updating m_selected
      m_selected = selectable;
	    
      const std::string option_name = selectable->getText();
      SelectionGroupEvent evt(this, option_name);
      this->fireEvent(evt);
    }
    return true;
  };

  return res;
}

} // namespace wl
