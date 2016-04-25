#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include "Widget.hpp"

#include "SelectorEvent.hpp"
#include "SelectorObserver.hpp"

namespace wl {

/**
 * An abstract base class for checkboxes and radio buttons.
 */
class Selector : public Widget
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
  bool isSet() const;

  /**
   * Sets (selects) the selector.
   */
  void set();

  /**
   * Resets (deselects) the selector.
   */
  void reset();

  /**
   * Toggles the selection of the selector.
   *
   * \return \c true if the selector is set (selected); \c false otherwise.
   */
  bool toggle();

  /**
   * Subscribes a selector observer (if the same observer is not already
   * subscribed) to this widget. The observer will be notified when a
   * \c SelectorEvent is fired by this widget.
   *
   * \param observer The observer to subscribe.
   */
  void addSelectorObserver(std::shared_ptr<SelectorObserver> observer);

  /**
   * Unsubscribes the \c SelectorObserver with the given index if it exists.
   * This method does nothing if the element with index \a index does not exist.
   *
   * \param index The index of the \c SelectorObserver to unsubscribe.
   */
  void removeSelectorObserver(std::shared_ptr<SelectorObserver> observer);

  /**
   * This method notifies all the observers that are subscribed to the
   * <tt>SelectorEvent</tt>s  events of this selector.
   *
   * \param evt The event to fire.
   */
  void fireSelectorEvent(const SelectorEvent& evt);
  
protected:
  bool send_selector_evt_to_observers(const SelectorEvent& evt);
private:
  std::vector< std::shared_ptr<SelectorObserver> > m_observers;
  bool m_set;
};

} // namespace wl

#endif // SELECTOR_HPP
