#ifndef SELECTION_EVENT_HPP
#define SELECTION_EVENT_HPP

#include "Event.hpp"

namespace wl {

class SelectionEvent : public Event
{
public:
  enum SELECTION_EVT_TYPE
  {
    SELECTION_SET,
    SELECTION_RESET
  };

  SelectionEvent(Widget *source,
		 SELECTION_EVT_TYPE type)
    : Event(source),
      m_type(type)
  {
  }

  virtual ~SelectionEvent() {}

  SELECTION_EVT_TYPE getEvtType() const
  {
    return m_type;
  }
  
private:
  const SELECTION_EVT_TYPE m_type;
};

} // namespace wl

#endif // SELECTION_EVENT_HPP
