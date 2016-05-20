#ifndef RESIZE_EVENT_HPP
#define RESIZE_EVENT_HPP

#include "WidgetLib/evt/Event.hpp"

namespace wl {

class ResizeEvent : public Event
{
public:
  ResizeEvent(Widget *source,
	      int new_width,
	      int new_height)
    : Event(source),
      m_new_width(new_width),
      m_new_height(new_height)
  {
  }

  virtual ~ResizeEvent() {}

  int getNewWidth() const
  {
    return m_new_width;
  }

  int getNewHeight() const
  {
    return m_new_height;
  }
  
private:
  const int m_new_width;
  const int m_new_height;
};

} // namespace wl

#endif // RESIZE_EVENT_HPP
