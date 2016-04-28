#include "Selectable.hpp"

namespace wl {

Selectable::Selectable(Vec2 position,
		       int width,
		       int height,
		       std::string text)
  : Label(position, width, height, text),
    m_normal_bg(255, 255, 255),
    m_selected_bg(0, 0, 255),
    m_normal_text(0, 0, 0),
    m_selected_text(255, 255, 255)
{
  // Setting colours
  set_normal_colours();
}

Selectable::~Selectable()
{
}

bool Selectable::isSelected() const
{
  return m_selected;
}

void Selectable::select()
{
  m_selected = true;
  set_selected_colours();
}

void Selectable::deselect()
{
  m_selected = false;
  set_normal_colours();
}

genv::color Selectable::getNormalBackgroundColour() const
{
  return m_normal_bg;
}

void Selectable::setNormalBackgroundColour(genv::color colour)
{
  m_normal_bg = colour;
}

genv::color Selectable::getSelectedBackgroundColour() const
{
  return m_selected_bg;
}

void Selectable::setSelectedBackgroundColour(genv::color colour)
{
  m_selected_bg = colour;
}

genv::color Selectable::getNormalTextColour() const
{
  return m_normal_text;
}

void Selectable::setNormalTextColour(genv::color colour)
{
  m_normal_text = colour;
}

genv::color Selectable::getSelectedTextColour() const
{
  return m_selected_text;
}

void Selectable::setSelectedTextColour(genv::color colour)
{
  m_selected_text = colour;
}

// Private
void Selectable::set_normal_colours()
{
  setBackgroundColour(m_normal_bg);
  TextDisplay::set_text_colour(m_normal_text);
}

void Selectable::set_selected_colours()
{
  setBackgroundColour(m_selected_bg);
  TextDisplay::set_text_colour(m_selected_text);
}

} // namespace wl
