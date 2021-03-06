#ifndef TEXT_DISPLAY_HPP
#define TEXT_DISPLAY_HPP

#include "WidgetLib/Widget.hpp"

#include <graphics.hpp>

namespace wl {

class TextDisplay : public Widget
{
public:
  TextDisplay(Vec2 position,
	      int width,
	      int height,
	      std::string text = {});
  
  virtual ~TextDisplay();

  virtual void paint() override;
  
protected:
  const genv::color& get_text_colour() const;
  void set_text_colour(genv::color colour);
  
  // Returns the width of a character on the canvas of \a widget.
  int get_char_width() const;

  // Returns the width of a character on the canvas of \a widget.
  int get_char_height() const;
  
  int get_num_of_displayable_chars() const;
  virtual std::string get_text_to_display() const = 0;

  // Fields
  std::string m_text;
  unsigned int m_horiz_inset;

  genv::color m_text_colour;
};

} // namespace wl

#endif // TEXT_DISPLAY_HPP
