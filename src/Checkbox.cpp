#include "Checkbox.hpp"

#include "Util.hpp"

namespace wl {

Checkbox::Checkbox(Vec2 position,
		   int width,
		   int height)
  : Widget(position, width, height),
    m_observers()
{
}

Checkbox::~Checkbox()
{
}

bool Checkbox::isSet() const
{
  return m_set;
}

void Checkbox::set()
{
  m_set = true;
}

void Checkbox::reset()
{
  m_set = false;
}

bool Checkbox::toggle()
{
  bool old_value = m_set;
  m_set = !m_set;
  return old_value;
}

void Checkbox::addCheckboxObserver(std::shared_ptr<CheckboxObserver> observer)
{
  add_to_vec_uniquely(m_observers, observer);
}

void Checkbox::removeCheckboxObserver(
				 std::shared_ptr<CheckboxObserver> observer)
{
  remove_from_vec(m_observers, observer);
}

void Checkbox::fireCheckboxEvent(const CheckboxEvent& evt)
{
  send_checkbox_evt_to_observers(evt);
}

void Checkbox::paint()
{
  // TODO.
}

// Protected
bool Checkbox::send_checkbox_evt_to_observers(const CheckboxEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr<CheckboxObserver> observer : m_observers)
  {
    if (observer)
      handled |= observer->handleCheckboxEvent(evt);
  }

  return handled;
}

}
