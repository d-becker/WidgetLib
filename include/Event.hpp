#ifndef EVENT_HPP
#define EVENT_HPP

namespace wl {

class Widget;

class Event
{
public:
  Event(Widget *source)
    : m_source(source)
  {
  }

  virtual ~Event()
  {
  }

  /**
   * Returns a pointer to the widget that is the source of the event.
   *
   * \return A pointer to the widget that is the source of the event.
   */
  Widget *getWidgetSource()
  {
    return m_source;
  }
  
private:
  Widget * const m_source;
};

} // namespace wl

#endif // EVENT_HPP
