#ifndef KEY_EVENT_HPP
#define KEY_EVENT_HPP

#include "Event.hpp"

namespace wl {

class KeyEvent : public Event
{
public:
  enum KEY_EVT_TYPE
  {
    KEY_PRESSED,
    KEY_RELEASED
  };

  KeyEvent(Widget *source,
	   KEY_EVT_TYPE type,
	   int keycode)
    : Event(source),
      m_type(type),
      m_keycode(keycode)
  {
  }

  virtual ~KeyEvent()
  {
  }

  KEY_EVT_TYPE getEvtType() const
  {
    return m_type;
  }

  int getKeycode() const
  {
    return m_keycode;
  }
  
private:
  const KEY_EVT_TYPE m_type;
  const int m_keycode;
};

} // namespace wl

#endif // KEY_EVENT_HPP
