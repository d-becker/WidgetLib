#include "TextBox.hpp"

#include <cctype>
#include <memory>

#include "FocusObserver.hpp"
#include "FocusObserverAdapter.hpp"
#include "KeyObserver.hpp"
#include "KeyObserverAdapter.hpp"
#include "MouseObserver.hpp"
#include "MouseObserverAdapter.hpp"

namespace wl {

TextBox::TextBox(Container *parent,
		 Vec2 position,
		 int width,
		 int height,
		 std::string text)
  : Widget(parent, position, width, height),
    m_text(text),
    m_cursor(0),
    m_first_char_displayed(0),
    m_horiz_padding(2),
    m_focussed(false)
{
  addMouseObserver(std::make_shared<MouseObserverAdapter>([this](const MouseEvent& evt) {
	if (evt.getEvtType() == MouseEvent::MOUSE_BTN_PRESSED)
	{
	  if (!m_focussed)
	    grabFocus();

	  if (evt.getMouseButton() == MouseEvent::MOUSE_BTN::LEFT)
	  {
	    Vec2 mouse_pos = evt.getMousePos();
	    set_cursor_by_mouse(mouse_pos.x);
	  }
	}
	return true;
      }));

  addKeyObserver(std::make_shared<KeyObserverAdapter>([this](const KeyEvent& evt) {
	using namespace genv;
	if (evt.getEvtType() == KeyEvent::KEY_PRESSED)
	{
	  int keycode = evt.getKeycode();
	  switch (keycode)
	  {
	  case key_left: {decrement_cursor(); break;}
	  case key_right: {increment_cursor(); break;}
	  case key_end: {cursor_end(); break;}
	  case key_home: {cursor_home(); break;}
	  case key_backspace: {backspace(); break;}
	  case key_delete: {del(); break;}
	  default: {write_char(keycode); break;}
	  }
	}

	return true;
      }));

  addFocusObserver(std::make_shared<FocusObserverAdapter>([this](const FocusEvent& evt) {
	if (evt.getEvtType() == FocusEvent::FOCUS_GAINED)
	  m_focussed = true;
	else if (evt.getEvtType() == FocusEvent::FOCUS_LOST)
	  m_focussed = false;

	return false;
      }));
}

TextBox::~TextBox()
{
}

std::string TextBox::getText() const
{
  return m_text;
}

void TextBox::setText(std::string text)
{
  m_text = text;
}

void TextBox::paint()
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
    int char_width = get_char_width();
    int text_level = getHeight() / 2 - char_height / 2;
    canv << move_to(m_horiz_padding, text_level)
         << color(0, 0, 0)
         << text(get_text_to_display());

    // Cursor
    if (m_focussed)
    {
      canv << move_to(m_horiz_padding + m_cursor * char_width, text_level)
	   << line(0, char_height);
    }
  }
}

// Protected
int TextBox::get_cursor() const
{
  return m_cursor;
}

void TextBox::increment_cursor()
{
  if (m_cursor < m_text.size())
    ++m_cursor;

  adjust_display();
}

void TextBox::decrement_cursor()
{
  if (m_cursor > 0)
    --m_cursor;

  adjust_display();
}

void TextBox::set_cursor_by_mouse(int x_pos_abs)
{
  int x_pos_rel = x_pos_abs - getAbsPosition().x; // In the coordinate system
					      // of this widget
  int char_width = get_char_width();
  
  int dist_from_text_beginning = x_pos_rel - m_horiz_padding;
  int cursor_pos_floor = dist_from_text_beginning / char_width;
  int remainder = dist_from_text_beginning % char_width;

  // Choose the cursor position that is the nearest to the mouse pointer
  int cursor_pos = remainder < char_width / 2 ?
			       cursor_pos_floor : cursor_pos_floor + 1;
  set_cursor(cursor_pos);
}

void TextBox::set_cursor(int pos)
{
  if (pos < 0)
    m_cursor = 0;
  else if (pos > (int) m_text.size())
    m_cursor = m_text.size();
  else
    m_cursor = pos;

  adjust_display();
}

void TextBox::cursor_end()
{
  set_cursor(m_text.size());
}

void TextBox::cursor_home()
{
  set_cursor(0);
}

int TextBox::get_first_char_displayed() const
{
  return m_first_char_displayed;
}

void TextBox::increment_first_char_displayed(unsigned int n)
{
  int new_value = m_first_char_displayed + n;
  if (new_value < (int) m_text.size() - 1)
    m_first_char_displayed = new_value;
  else
    m_first_char_displayed = m_text.size() - 1;
}

void TextBox::decrement_first_char_displayed(unsigned int n)
{
  int new_value = m_first_char_displayed - n;
  if (new_value >= 0)
    m_first_char_displayed = new_value;
  else
    m_first_char_displayed = 0;
}

void TextBox::backspace()
{
  if (m_cursor > 0)
  {
    decrement_cursor();
    m_text.erase(m_cursor, 1);
  }
}

void TextBox::del()
{
  if (m_cursor < m_text.size())
    m_text.erase(m_cursor, 1);
}

void TextBox::write_char(char ch)
{
  if (!iscntrl(ch))
  {
    m_text.insert(m_cursor, 1, ch);
    increment_cursor();
  }
}

void TextBox::adjust_display()
{
  // Cursor out to the right
  if (m_first_char_displayed + get_num_of_displayable_chars() < m_cursor)
  {
    int repeat = m_cursor - get_num_of_displayable_chars()
                          - m_first_char_displayed;
    increment_first_char_displayed(repeat);
  }
  // Cursor out to the left
  else if (m_cursor < m_first_char_displayed)
  {
    int repeat = m_first_char_displayed - m_cursor;
    decrement_first_char_displayed(repeat);
  }

  // Empty space to the right
  int disp_text_length = get_text_to_display().size();
  int displayable_length = get_num_of_displayable_chars();
  if (disp_text_length < displayable_length)
  {
    int repeat = displayable_length - disp_text_length;
    decrement_first_char_displayed(repeat);
  }
}

int TextBox::get_char_width() const
{
  std::shared_ptr<const genv::canvas> canv_ptr = getCanvas();
  if (!canv_ptr)
    return 0;

  return canv_ptr->twidth(" ");
}

int TextBox::get_char_height() const
{
  std::shared_ptr<const genv::canvas> canv_ptr = getCanvas();
  if (!canv_ptr)
    return 0;

  return canv_ptr->cascent() + canv_ptr->cdescent();
}

int TextBox::get_num_of_displayable_chars() const
{
  int char_width = get_char_width();
  int available_width = getWidth() - 2 * m_horiz_padding;
  return available_width / char_width;
}

std::string TextBox::get_text_to_display() const
{
  int n_of_chars_to_disp = get_num_of_displayable_chars();
  return  m_text.substr(m_first_char_displayed, n_of_chars_to_disp);
}

} // namespace wl
