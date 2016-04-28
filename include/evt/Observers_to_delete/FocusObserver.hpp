#ifndef FOCUS_OBSERVER_HPP
#define FOCUS_OBSERVER_HPP

#include "FocusEvent.hpp"

namespace wl {

class FocusObserver
{
public:
  /**
   * Handles a focus event.
   *
   * \param evt The focus event to handle.
   *
   * \return \c true if the event has been fully handled and need not be
   *         propagated to the parent; \c false otherwise.
   */
  virtual bool handleFocusEvent(const FocusEvent& evt) = 0;
};

} // namespace wl

#endif // FOCUS_OBSERVER_HPP
