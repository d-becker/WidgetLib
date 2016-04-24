#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <memory>

#include "ButtonEvent.hpp"
#include "ButtonObserver.hpp"
#include "MouseEvent.hpp"
#include "Widget.hpp"

#include <memory>
#include <functional>
#include <vector>

namespace wl {

class Button : public Widget
{
public:
  Button(Vec2 position = Vec2(0, 0),
	 int width = 50,
	 int height = 50);

  virtual ~Button();

  /**
   * Subscribes a button observer (if the same observer is not already
   * subscribed) to this widget. The observer will be notified when a
   * \c ButtonEvent is fired by this widget.
   *
   * \param observer The observer to subscribe.
   */
  void addButtonObserver(std::shared_ptr<ButtonObserver> observer);

  /**
   * Unsubscribes the \c ButtonObserver with the given index if it exists.
   * This method does nothing if the element with index \a index does not exist.
   *
   * \param index The index of the \c ButtonObserver to unsubscribe.
   */
  void removeButtonObserver(std::shared_ptr<ButtonObserver> observer);

  /**
   * This method notifies all the observers that are subscribed to
   * the events of this <tt>ButtonEvent</tt>s of this button.
   *
   * \param evt The event to fire.
   */
  void fireButtonEvent(const ButtonEvent& evt);
  
  virtual void paint() override;

protected:
  bool send_button_evt_to_observers(const ButtonEvent& evt);
  
private:
  std::vector< std::shared_ptr<ButtonObserver> > m_observers;
};

} // namespace wl

#endif // BUTTON_HPP
