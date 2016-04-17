#ifndef RESIZE_OBSERVER_HPP
#define RESIZE_EVENT_HPP

#include "ResizeEvent.hpp"

namespace wl {

class ResizeObserver
{
public:
  virtual ~ResizeObserver() {}

   /**
   * Handles a resize event.
   *
   * \param evt The resize event to handle.
   *
   * \return \c true if the event has been fully handled and need not be
   *         propagated to the parent; \c false otherwise.
   */
  virtual bool handleResizeEvent(const ResizeEvent& evt) = 0;
};

} // namespace wl

#endif // RESIZE_EVENT_HPP
