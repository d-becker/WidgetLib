#ifndef SELECTION_OBSERVER_HPP
#define SELECTION_OBSERVER_HPP

#include "SelectionEvent.hpp"

namespace wl {

class SelectionObserver
{
public:
  virtual ~SelectionObserver() {}

  /**
   * Handles a selection event.
   *
   * \param evt The selection event to handle.
   *
   * \return \c true if the event has been fully handled and need not be
   *         propagated to the parent; \c false otherwise.
   */
  virtual bool handleSelectionEvent(const SelectionEvent& evt) = 0;
};

} // namespace wl

#endif // SELECTION_OBSERVER_HPP
