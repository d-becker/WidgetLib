#ifndef SELECTOR_EVENT_HPP
#define SELECTOR_EVENT_HPP

#include "Event.hpp"

namespace wl {

class SelectorEvent : public Event
{
public:
  enum SELECTOR_EVT_TYPE
  {
    SELECTOR_SET,
    SELECTOR_RESET
  };

  SelectorEvent(Widget *source,
		SELECTOR_EVT_TYPE type)
    : Event(source),
      m_type(type)
  {
  }

  virtual ~SelectorEvent() {}

  SELECTOR_EVT_TYPE getEvtType() const
  {
    return m_type;
  }
  
private:
  const SELECTOR_EVT_TYPE m_type;
};

} // namespace wl

#endif // SELECTOR_EVENT_HPP
