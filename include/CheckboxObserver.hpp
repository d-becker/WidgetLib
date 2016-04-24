#ifndef CHECKBOX_OBSERVER_HPP
#define CHECKBOX_OBSERVER_HPP

#include "CheckboxEvent.hpp"

namespace wl {

class CheckboxObserver
{
public:
  virtual ~CheckboxObserver() {}

  /**
   * Handles a checkbox event.
   *
   * \param evt The checkbox event to handle.
   *
   * \return \c true if the event has been fully handled and need not be
   *         propagated to the parent; \c false otherwise.
   */
  virtual bool handleCheckboxEvent(const CheckboxEvent& evt) = 0;
};

} // namespace wl

#endif // CHECKBOX_OBSERVER_HPP
