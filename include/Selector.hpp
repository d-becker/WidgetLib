#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include "Widget.hpp"

#include "SelectionEvent.hpp"
#include "SelectionObserver.hpp"

namespace wl {

/**
 * An abstract base class for checkboxes and radio buttons.
 */
class Selector : public virtual Widget
{
public:
  Selector(Vec2 position = Vec2(0, 0),
	   int width = 50,
	   int height = 50);

  virtual ~Selector();

  /**
   * Returns whether the selector is set (selected).
   *
   * \return \c true if the selector is set (selected); \c false otherwise.
   */
  bool isSelected() const;

  /**
   * Sets (selects) the selector.
   */
  void select();

  /**
   * Resets (deselects) the selector.
   */
  void deselect();

  /**
   * Toggles the selection of the selector.
   *
   * \return \c true if the selector is set (selected); \c false otherwise.
   */
  bool toggle();

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
  bool m_selected;
};

} // namespace wl

#endif // SELECTOR_HPP
