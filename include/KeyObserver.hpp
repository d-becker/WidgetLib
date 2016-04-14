#ifndef KEY_OBSERVER_HPP
#define KEY_OBSERVER_HPP

#include "KeyEvent.hpp"

namespace wl {

class KeyObserver
{
public:
  /**
   * Handles a key event.
   *
   * \param evt The key event to handle.
   *
   * \return \c true if the event has been fully handled and need not be
   *         propagated to the parent; \c false otherwise.
   */
  virtual bool handleKeyEvent(const KeyEvent& evt) = 0;
};

} // namespace wl

#endif // KEY_OBSERVER_HPP
