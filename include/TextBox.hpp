#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "Widget.hpp"

#include <string>

#include "Container.hpp"
#include "Vec2.hpp"

namespace wl {

/**
 * A single line text entry box.
 */
class TextBox : public Widget
{
public:
  TextBox(Container *parent,
	  Vec2 position = Vec2(0, 0),
	  int width = 50,
	  int height = 20,
	  std::string text = {});

  virtual ~TextBox();

  std::string getText() const;
  void setText(std::string text);

  virtual void paint() override;
  
protected:
  int get_cursor() const;  
  void increment_cursor();
  void decrement_cursor();

  void set_cursor(int pos);
  void cursor_end();
  void cursor_home();

  int get_first_char_displayed() const;
  void increment_first_char_displayed(unsigned int n = 1);
  void decrement_first_char_displayed(unsigned int n = 1);

  void backspace();
  void del();
  void write_char(char ch);

  void adjust_display();

  int get_char_width() const;
  int get_num_of_displayable_chars() const;
  std::string get_text_to_display() const;
private:
  std::string m_text;
  unsigned int m_cursor;
  unsigned int m_first_char_displayed;
};

} // namespace wl

#endif // TEXTBOX_HPP
