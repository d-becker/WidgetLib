#include "Selector.hpp"

#include "Util.hpp"

namespace wl {

Selector::Selector(Vec2 position,
		   int width,
		   int height)
  : Widget(position, width, height),
    m_observers(),
    m_super_observers(),
    m_selected(false)
{
}

Selector::~Selector()
{
}

bool Selector::isSelected() const
{
  return m_selected;
}

void Selector::select()
{
  m_selected = true;
  SelectionEvent event(this, SelectionEvent::SELECTION_SET);
  fireSelectionEvent(event);
}

void Selector::deselect()
{
  m_selected = false;
  SelectionEvent event(this, SelectionEvent::SELECTION_RESET);
  fireSelectionEvent(event);
}

bool Selector::toggle()
{
  bool old_value = m_selected;
  if (old_value)
    deselect();
  else
    select();
  return old_value;
}

void Selector::addSelectionObserver(std::shared_ptr<SelectionObserver> observer)
{
  add_to_vec_uniquely(m_observers, observer);
}

void Selector::removeSelectionObserver(
				   std::shared_ptr<SelectionObserver> observer)
{
  remove_from_vec(m_observers, observer);
}

void Selector::fireSelectionEvent(const SelectionEvent& evt)
{
  send_selection_evt_to_observers(evt);
}

// Protected
void Selector::addSelectionSuperObserver(
				   std::shared_ptr<SelectionObserver> observer)
{
  add_to_vec_uniquely(m_super_observers, observer);
}

bool Selector::send_selection_evt_to_observers(const SelectionEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr<SelectionObserver> observer : m_observers)
  {
    if (observer)
      handled |= observer->handleSelectionEvent(evt);
  }

  for (std::shared_ptr<SelectionObserver> observer : m_super_observers)
  {
    if (observer)
      handled |= observer->handleSelectionEvent(evt);
  }

  return handled;
}

} // namespace wl
