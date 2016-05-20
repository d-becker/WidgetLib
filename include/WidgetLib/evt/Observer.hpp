#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "WidgetLib/evt/Event.hpp"

namespace wl {

/**
 * A base class for observers. The template parameter should be a subclass type
 * of the \c Event class.
 *
 * \param E A subclass of <tt>Event</tt>.
 */
template<typename E>
class Observer
{
public:
  /**
   * Handles an event.
   *
   * \param evt The event to handle.
   *
   * \return \c true if the event has been fully handled and need not be
   *         propagated to the parent; \c false otherwise.
   */
  virtual bool handleEvent(const E& evt) = 0;
};

} // namespace wl

#endif // OBSERVER_HPP
