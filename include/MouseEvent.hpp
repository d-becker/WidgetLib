#ifndef MOUSE_EVENT_EPP
#define MOUSE_EVENT_EPP

#include "Event.hpp"

#include "Vec2.hpp"

namespace wl {

class MouseEvent : public Event
{
public:

  enum MOUSE_EVT_TYPE
  {
    MOUSE_BTN_PRESSED,
    MOUSE_BTN_RELEASED,
    MOUSE_MOVED,
    MOUSE_ENTERED,
    MOUSE_LEFT,
    CLICKED_ON_WIDGET
  };

  enum class MOUSE_BTN
  {
    NONE,
    LEFT,
    MIDDLE,
    RIGHT
  };

  MouseEvent(Widget *source,
	     Vec2 mouse_pos,
	     MOUSE_EVT_TYPE type,
	     MOUSE_BTN btn)
    : Event(source),
      m_mouse_pos(mouse_pos),
      m_type(type),
      m_btn(btn)
  {
  }

  virtual ~MouseEvent() {}

  Vec2 getMousePos() const
  {
    return m_mouse_pos;
  }

  MOUSE_EVT_TYPE getEvtType() const
  {
    return m_type;
  }

  MOUSE_BTN getMouseButton() const
  {
    return m_btn;
  }
  
private:
  const Vec2 m_mouse_pos;
  const MOUSE_EVT_TYPE m_type;
  const MOUSE_BTN m_btn;
};

} // namespace wl

#endif // MOUSE_EVENT_EPP
