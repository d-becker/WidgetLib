#ifndef BUTTON_OBSERVER_HPP
#define BUTTON_OBSERVER_HPP

#include "ButtonEvent.hpp"

namespace wl {

class ButtonObserver
{
public:
  /**
   * Handles a button event.
   *
   * \param evt The mouse event to handle.
   *
   * \return \c true if the event has been fully handled and need not be
   *         propagated to the parent; \c false otherwise.
   */
  virtual bool handleButtonEvent(const ButtonEvent& evt) = 0;
};

} // namespace wl

#endif // BUTTON_OBSERVER_HPP
