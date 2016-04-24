#ifndef CHECKBOX_EVENT_HPP
#define CHECKBOX_EVENT_HPP

#include "Event.hpp"

namespace wl {

class CheckboxEvent : public Event
{
public:
  enum CHECKBOX_EVT_TYPE
  {
    CHECKBOX_SET,
    CHECKBOX_RESET
  };

  CheckboxEvent(Widget *source,
		CHECKBOX_EVT_TYPE type)
    : Event(source),
      m_type(type)
  {
  }

  virtual ~CheckboxEvent() {}

  CHECKBOX_EVT_TYPE getEvtType() const
  {
    return m_type;
  }
  
private:
  const CHECKBOX_EVT_TYPE m_type;
};

} // namespace wl

#endif // CHECKBOX_EVENT_HPP
