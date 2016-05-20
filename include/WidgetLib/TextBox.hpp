#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "WidgetLib/TextDisplay.hpp"

#include <string>

#include "WidgetLib/Container.hpp"
#include "WidgetLib/Vec2.hpp"

namespace wl {

/**
 * A single line text entry box.
 */
class TextBox : public TextDisplay
{
public:
  TextBox(Vec2 position,
	  int width,
	  int height,
	  std::string text = {});

  virtual ~TextBox();

  std::string getText() const;
  void setText(std::string text);

  virtual void paint() override;
  
protected:
  int get_cursor() const;  
  void increment_cursor();
  void decrement_cursor();

  void set_cursor_by_mouse(int x_pos_abs);
  void set_cursor(int pos);
  void cursor_end();
  void cursor_home();

  int get_first_char_displayed() const;
  void increment_first_char_displayed(unsigned int n = 1);
  void decrement_first_char_displayed(unsigned int n = 1);

  void backspace();
  void del();
  bool write_char(char ch);

  void adjust_display();
  virtual std::string get_text_to_display() const override;
  
private:
  unsigned int m_cursor;
  unsigned int m_first_char_displayed;

  bool m_focussed;
};

} // namespace wl

#endif // TEXTBOX_HPP
