#ifndef FOCUS_EVENT_HPP
#define FOCUS_EVENT_HPP

#include "Event.hpp"

namespace wl {

class FocusEvent : public Event
{
public:
  enum FOCUS_EVT_TYPE
  {
    FOCUS_GAINED,
    FOCUS_LOST
  };

  FocusEvent(Widget *source,
	     FOCUS_EVT_TYPE type)
    : Event(source),
      m_type(type)
  {
  }

  virtual ~FocusEvent()
  {
  }

  FOCUS_EVT_TYPE getEvtType() const
  {
    return m_type;
  }

private:
  const FOCUS_EVT_TYPE m_type;
};

} // namespace wl

#endif // FOCUS_EVENT_HPP
