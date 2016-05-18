#include "Toplevel.hpp"

#include <cmath>

#include <graphics.hpp>

#include "evt/FocusEvent.hpp"
#include "evt/KeyEvent.hpp"
#include "evt/MouseEvent.hpp"

namespace wl {

Toplevel::Toplevel(int width,
		   int height,
		   unsigned int refresh_rate)
  : FreePanel(Vec2(0, 0), width, height),
    m_mouse_btn_left_pressed(nullptr),
    //m_mouse_btn_right_pressed(nullptr),
    m_mouse_inside(nullptr),
    m_focussed(nullptr),
    m_refresh_rate(refresh_rate),
    m_looping(false)
{
}

Toplevel::~Toplevel()
{
}

Toplevel *Toplevel::getToplevel()
{
  return this;
}

void Toplevel::mainloop()
{
  using namespace genv;
  gout.open(getWidth(), getHeight());

  m_looping = true;
  gin.timer(m_refresh_rate);
  event ev;
  while (gin >> ev && m_looping)
  {
    if (ev.type == ev_timer)
    {
      paint();
      gout << stamp(*getCanvas(), 0, 0) << refresh;
    } else
    {    
      handle_genv_event(ev);
    }
  }
}

void Toplevel::stopMainLoop()
{
  m_looping = false;
}

Widget *Toplevel::getFocussed() const
{
  return m_focussed;
}

void Toplevel::setFocussed(Widget *focussed)
{
  if (focussed != m_focussed)
  {
    // Sending focus lost event
    if (m_focussed)
    {
      FocusEvent evt(m_focussed, FocusEvent::FOCUS_LOST);
      m_focussed->fireFocusEvent(evt);
    }

    // Sending focus gained event
    if (focussed)
    {
      FocusEvent evt(focussed, FocusEvent::FOCUS_GAINED);
      focussed->fireFocusEvent(evt);
    }

    // Updating m_focussed
    m_focussed = focussed;
  }
}

// Private

void Toplevel::handle_genv_event(const genv::event& g_evt)
{
  switch (g_evt.type)
  {
    case genv::ev_mouse : {handle_genv_mouse_event(g_evt); break;}
    case genv::ev_key : {handle_genv_key_event(g_evt); break;}
    default: break;
  }
}

void Toplevel::handle_genv_mouse_event(const genv::event& g_evt)
{
  if (g_evt.button == 0) // No button.
			 // Relying on genv::event.button being 0 in this case.
  {
    handle_genv_mouse_event_no_button(g_evt);
  } else // A button has been pressed or released
  {
    handle_genv_mouse_event_button(g_evt);
  }
}

void Toplevel::handle_genv_mouse_event_no_button(const genv::event& g_evt)
{
  Vec2 mouse_position = Vec2(g_evt.pos_x, g_evt.pos_y);
  Widget *widget_under_cursor = getWidgetAtPos(mouse_position);
  const MouseEvent::MOUSE_BTN button = MouseEvent::MOUSE_BTN::NONE;
  
  if (widget_under_cursor == m_mouse_inside) // The mouse has not
					     // left the widget
  {
    if (m_mouse_inside)
      m_mouse_inside->fireMouseEvent(
				   MouseEvent(m_mouse_inside, mouse_position,
				              MouseEvent::MOUSE_MOVED, button));
  } else // The mouse has left the widget and/or entered another one
  {
    if (m_mouse_inside) // Notify the widget that the mouse left
      m_mouse_inside->fireMouseEvent(MouseEvent(m_mouse_inside,
						mouse_position,
						MouseEvent::MOUSE_LEFT,
						button));
      
    if (widget_under_cursor) // Notify the widget that the mouse entered
      widget_under_cursor->fireMouseEvent(MouseEvent(widget_under_cursor,
						     mouse_position,
						     MouseEvent::MOUSE_ENTERED,
						     button));
    // Update m_mouse_inside
    m_mouse_inside = widget_under_cursor;
  }
}

void Toplevel::handle_genv_mouse_event_button(const genv::event& g_evt)
{
  // Filtering out wheel events
  if (g_evt.button == genv::btn_wheelup)
  {
    Vec2 mouse_position = Vec2(g_evt.pos_x, g_evt.pos_y);
    Widget *widget_under_cursor = getWidgetAtPos(mouse_position);
    MouseEvent::MOUSE_EVT_TYPE type = MouseEvent::MOUSE_WHEEL_UP;
    MouseEvent::MOUSE_BTN button = MouseEvent::MOUSE_BTN::NONE;
    if (widget_under_cursor)
      widget_under_cursor->fireMouseEvent(
	       MouseEvent(widget_under_cursor, mouse_position, type,  button));
  } else if (g_evt.button == genv::btn_wheeldown)
  {
    Vec2 mouse_position = Vec2(g_evt.pos_x, g_evt.pos_y);
    Widget *widget_under_cursor = getWidgetAtPos(mouse_position);
    MouseEvent::MOUSE_EVT_TYPE type = MouseEvent::MOUSE_WHEEL_DOWN;
    MouseEvent::MOUSE_BTN button = MouseEvent::MOUSE_BTN::NONE;
    if (widget_under_cursor)
      widget_under_cursor->fireMouseEvent(
	       MouseEvent(widget_under_cursor, mouse_position, type,  button));
  } else
  {
    handle_genv_mouse_event_normal_button(g_evt);
  }
}

void Toplevel::handle_genv_mouse_event_normal_button(const genv::event& g_evt)
{
  Vec2 mouse_position = Vec2(g_evt.pos_x, g_evt.pos_y);
  Widget *widget_under_cursor = getWidgetAtPos(mouse_position);

  MouseEvent::MOUSE_EVT_TYPE type;
  MouseEvent::MOUSE_BTN button;
  
  // Determining the button
  switch (abs(g_evt.button))
  {
    case genv::btn_left : {button = MouseEvent::MOUSE_BTN::LEFT; break;}
    case genv::btn_middle : {button = MouseEvent::MOUSE_BTN::MIDDLE; break;}
    case genv::btn_right : {button = MouseEvent::MOUSE_BTN::RIGHT; break;}
  }

  // Determining if the button was pressed or released
  if (g_evt.button > 0)
    type = MouseEvent::MOUSE_BTN_PRESSED;
  else
    type = MouseEvent::MOUSE_BTN_RELEASED;

  // Creating the event(s)
  if (widget_under_cursor)
  {
    // Normal low level event
    MouseEvent event(widget_under_cursor, mouse_position, type, button);
    widget_under_cursor->fireMouseEvent(event);

    // Creating MouseEvent::CLICKED_ON_WIDGET event if the left button has been
    // released on the widget on which it was pressed before
    if (button == MouseEvent::MOUSE_BTN::LEFT
	&& type == MouseEvent::MOUSE_BTN_RELEASED
        && widget_under_cursor == m_mouse_btn_left_pressed)
    {
      MouseEvent clicked_event(widget_under_cursor, mouse_position,
			       MouseEvent::CLICKED_ON_WIDGET, button);
      widget_under_cursor->fireMouseEvent(clicked_event);
    }
  }

  // Updating m_mouse_btn_left_pressed
  if (button == MouseEvent::MOUSE_BTN::LEFT)
  {
    if (type == MouseEvent::MOUSE_BTN_PRESSED)
      m_mouse_btn_left_pressed = widget_under_cursor;
    else if (type == MouseEvent::MOUSE_BTN_RELEASED)
      m_mouse_btn_left_pressed = nullptr;
  }
}

void Toplevel::handle_genv_key_event(const genv::event& g_evt)
{
  KeyEvent::KEY_EVT_TYPE type = g_evt.keycode > 0 ? KeyEvent::KEY_PRESSED
                                                  : KeyEvent::KEY_RELEASED;
  // In the case of key events, in contrast to other events, first the Toplevel
  // gets a chance to handle the event and only if the Toplevel didn't indicate
  // that it fully handled the event will it be sent to the focussed widget.
  // After that, the propagation to parent widgets is done as usual.
  KeyEvent evt(this, type, g_evt.keycode);
  bool handled = send_key_evt_to_observers(evt);

  if (!handled && m_focussed) // If a widget is in focus,
			      // that widget receives the event.
  {
    KeyEvent w_evt(m_focussed, type, g_evt.keycode);
    m_focussed->fireKeyEvent(w_evt);
  }
}

} // namespace wl
