#ifndef MOUSE_OBSERVER_HPP
#define MOUSE_OBSERVER_HPP

#include "MouseEvent.hpp"

namespace wl {

class MouseObserver
{
public:
  /**
   * Handles a mouse event.
   *
   * \param evt The mouse event to handle.
   *
   * \return \c true if the event has been fully handled and need not be
   *         propagated to the parent; \c false otherwise.
   */
  virtual bool handleMouseEvent(const MouseEvent& evt) = 0;
};

} // namespace wl

#endif // MOUSE_OBSERVER_HPP
