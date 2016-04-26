#ifndef SELECTION_EVENT_SOURCE_HPP
#define SELECTION_EVENT_SOURCE_HPP

#include <memory>
#include <vector>

#include "SelectionEvent.hpp"
#include "SelectionObserver.hpp"

namespace wl {

class SelectionEventSource
{
public:
  /**
   * Subscribes a selection observer (if the same observer is not already
   * subscribed) to this widget. The observer will be notified when a
   * \c SelectionEvent is fired by this widget.
   *
   * \param observer The observer to subscribe.
   */
  void addSelectionObserver(std::shared_ptr<SelectionObserver> observer);

  /**
   * Unsubscribes the \c SelectionObserver with the given index if it exists.
   * This method does nothing if the element with index \a index does not exist.
   *
   * \param index The index of the \c SelectionObserver to unsubscribe.
   */
  void removeSelectionObserver(std::shared_ptr<SelectionObserver> observer);

  /**
   * This method notifies all the observers that are subscribed to the
   * <tt>SelectionEvent</tt>s  events of this selector.
   *
   * \param evt The event to fire.
   */
  void fireSelectionEvent(const SelectionEvent& evt);
  
protected:
  void addSelectionSuperObserver(std::shared_ptr<SelectionObserver> observer);
  bool send_selection_evt_to_observers(const SelectionEvent& evt);
private:
  std::vector< std::shared_ptr<SelectionObserver> > m_observers;
  std::vector< std::shared_ptr<SelectionObserver> > m_super_observers;
};

} // namespace wl

#endif // SELECTION_EVENT_SOURCE_HPP
