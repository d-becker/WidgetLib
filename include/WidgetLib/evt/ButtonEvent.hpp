#ifndef BUTTON_EVENT_HPP
#define BUTTON_EVENT_HPP

#include "WidgetLib/evt/Event.hpp"

namespace wl {

class ButtonEvent : public Event
{
public:
  ButtonEvent(Widget *source)
    : Event(source)
  {
  }

  virtual ~ButtonEvent() {}
};

} // namespace wl

#endif // BUTTON_EVENT_HPP
