#include "TextDisplay.hpp"

namespace wl {

TextDisplay::TextDisplay(Vec2 position,
			 int width,
			 int height,
			 std::string text)
  : Widget(position, width, height),
    m_text(text),
    m_horiz_inset(2)
{
}

TextDisplay:: ~TextDisplay()
{
}

void TextDisplay::paint()
{
  using namespace genv;
  if (auto canv_ptr = getCanvas())
  {
    // Painting the background
    canvas& canv = *canv_ptr;
    canv << move_to(0, 0)
	 << color(255, 255, 255)
	 << box(getWidth(), getHeight());

    // Painting the text
    int char_height = get_char_height();
    int text_level = getHeight() / 2 - char_height / 2;
    canv << move_to(m_horiz_inset, text_level)
         << color(0, 0, 0)
         << text(get_text_to_display());
  }
}

int TextDisplay::get_char_width() const
{
  std::shared_ptr<const genv::canvas> canv_ptr = getCanvas();
  if (!canv_ptr)
    return 0;

  return canv_ptr->twidth(" ");
}

int TextDisplay::get_char_height() const
{
  std::shared_ptr<const genv::canvas> canv_ptr = getCanvas();
  if (!canv_ptr)
    return 0;

  return canv_ptr->cascent() + canv_ptr->cdescent();
}
  
int TextDisplay::get_num_of_displayable_chars() const
{
  int char_width = get_char_width();
  int available_width = getWidth() - 2 * m_horiz_inset;
  return available_width / char_width;
}

} // namespace wl