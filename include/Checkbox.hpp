#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "Widget.hpp"

#include <memory>

#include "CheckboxEvent.hpp"
#include "CheckboxObserver.hpp"

namespace wl {

class Checkbox : public Widget
{
public:
  Checkbox(Vec2 position = Vec2(0, 0),
	   int width = 50,
	   int height = 50);

  virtual ~Checkbox();

  /**
   * Returns whether the checkbox is set (selected).
   *
   * \return \c true if the checkbox is set (selected); \c false otherwise.
   */
  bool isSet() const;

  /**
   * Sets (selects) the checkbox.
   */
  void set();

  /**
   * Resets (deselects) the checkbox.
   */
  void reset();

  /**
   * Toggles the selection of the checkbox.
   *
   * \return \c true if the checkbox is set (selected); \c false otherwise.
   */
  bool toggle();

  /**
   * Subscribes a checkbox observer (if the same observer is not already
   * subscribed) to this widget. The observer will be notified when a
   * \c CheckboxEvent is fired by this widget.
   *
   * \param observer The observer to subscribe.
   */
  void addCheckboxObserver(std::shared_ptr<CheckboxObserver> observer);

  /**
   * Unsubscribes the \c CheckboxObserver with the given index if it exists.
   * This method does nothing if the element with index \a index does not exist.
   *
   * \param index The index of the \c CheckboxObserver to unsubscribe.
   */
  void removeCheckboxObserver(std::shared_ptr<CheckboxObserver> observer);

  /**
   * This method notifies all the observers that are subscribed to the
   * <tt>CheckboxEvent</tt>s  events of this checkbox.
   *
   * \param evt The event to fire.
   */
  void fireCheckboxEvent(const CheckboxEvent& evt);

  virtual void paint() override;

protected:
  bool send_checkbox_evt_to_observers(const CheckboxEvent& evt);
  
private:
  std::vector< std::shared_ptr<CheckboxObserver> > m_observers;

  bool m_set;
};

} // namespace wl

#endif // CHECKBOX_HPP
