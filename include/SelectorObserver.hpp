#ifndef SELECTOR_OBSERVER_HPP
#define SELECTOR_OBSERVER_HPP

#include "SelectorEvent.hpp"

namespace wl {

class SelectorObserver
{
public:
  virtual ~SelectorObserver() {}

  /**
   * Handles a selector event.
   *
   * \param evt The selector
 event to handle.
   *
   * \return \c true if the event has been fully handled and need not be
   *         propagated to the parent; \c false otherwise.
   */
  virtual bool handleSelectorEvent(const SelectorEvent& evt) = 0;
};

} // namespace wl

#endif // SELECTOR_OBSERVER_HPP
