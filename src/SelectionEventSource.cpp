#include "SelectionEventSource.hpp"

#include "Util.hpp"

namespace wl {

void SelectionEventSource::addSelectionObserver(
				    std::shared_ptr<SelectionObserver> observer)
{
  add_to_vec_uniquely(m_observers, observer);
}

void SelectionEventSource::removeSelectionObserver(
				    std::shared_ptr<SelectionObserver> observer)
{
  remove_from_vec(m_observers, observer);
}

void SelectionEventSource::fireSelectionEvent(const SelectionEvent& evt)
{
  send_selection_evt_to_observers(evt);
}

// Protected
void SelectionEventSource::addSelectionSuperObserver(
				    std::shared_ptr<SelectionObserver> observer)
{
  add_to_vec_uniquely(m_super_observers, observer);
}

bool SelectionEventSource::send_selection_evt_to_observers(
						      const SelectionEvent& evt)
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
