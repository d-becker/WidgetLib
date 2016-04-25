#include "Selector.hpp"

#include "Util.hpp"

namespace wl {

Selector::Selector(Vec2 position,
	 int width,
	 int height)
  : Widget(position, width, height),
    m_observers(),
    m_set(false)
{
}

Selector::~Selector()
{
}

bool Selector::isSet() const
{
  return m_set;
}

void Selector::set()
{
  m_set = true;
  SelectorEvent event(this, SelectorEvent::SELECTOR_SET);
  fireSelectorEvent(event);
}

void Selector::reset()
{
  m_set = false;
  SelectorEvent event(this, SelectorEvent::SELECTOR_RESET);
  fireSelectorEvent(event);
}

bool Selector::toggle()
{
  bool old_value = m_set;
  if (old_value)
    reset();
  else
    set();
  return old_value;
}

void Selector::addSelectorObserver(std::shared_ptr<SelectorObserver> observer)
{
  add_to_vec_uniquely(m_observers, observer);
}

void Selector::removeSelectorObserver(
				      std::shared_ptr<SelectorObserver> observer)
{
  remove_from_vec(m_observers, observer);
}

void Selector::fireSelectorEvent(const SelectorEvent& evt)
{
  send_selector_evt_to_observers(evt);
}

// Protected
bool Selector::send_selector_evt_to_observers(const SelectorEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr<SelectorObserver> observer : m_observers)
  {
    if (observer)
      handled |= observer->handleSelectorEvent(evt);
  }

  return handled;
}

} // namespace wl
