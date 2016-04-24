#include "Label.hpp"

namespace wl {

Label::Label(Vec2 position,
	     int width,
	     int height,
	     std::string text)
  : TextDisplay(position, width, height, text)
{
  setBackgroundColour(192,192,192);
}

Label::~Label()
{
}

std::string Label::getText() const
{
  return m_text;
}

void Label::setText(std::string text)
{
  m_text = text;
}

// Protected
std::string Label::get_text_to_display() const
{
  int len = get_num_of_displayable_chars();
  return m_text.substr(0, len);
}

} // namespace wl
