#include "Selector.hpp"

#include "Util.hpp"

namespace wl {

Selector::Selector(Vec2 position,
		   int width,
		   int height)
  : Widget(position, width, height),
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
  fireEvent(event);
}

void Selector::deselect()
{
  m_selected = false;
  SelectionEvent event(this, SelectionEvent::SELECTION_RESET);
  fireEvent(event);
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

} // namespace wl
