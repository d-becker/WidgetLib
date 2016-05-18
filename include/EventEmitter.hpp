#ifndef EVENT_EMITTER_HPP
#define EVENT_EMITTER_HPP

#include <memory>
#include <vector>

#include "evt/Observer.hpp"
#include "Util.hpp"
#include "Widget.hpp"

namespace wl {

class Widget;

/**
 * A class that handles registering observers and firing events that never
 * propagate upwards.
 */
template <typename EV>
class EventEmitter
{
public:
  EventEmitter()
  {
  }
  
  /**
   * Subscribes an observer (if the same observer is not already
   * subscribed) to this widget. The observer will be notified when an event
   * of the appropriate type is fired by this widget.
   *
   * \param observer The observer to subscribe.
   */
  void addObserver(std::shared_ptr< Observer<EV> > observer)
  {
    add_to_vec_uniquely(m_observers, observer);
  }

  /**
   * Unsubscribes the given observer if it exists.
   * This method does nothing if the element does not exist.
   *
   * \param index The index of the observer to unsubscribe.
   */
  void removeObserver(std::shared_ptr< Observer<EV> > observer)
  {
    remove_from_vec(m_observers, observer);
  }

  /**
   * This method notifies all the observers that are subscribed to the events.
   *
   * \param evt The event to fire.
   */
  void fireEvent(const EV& evt)
  {
    send_evt_to_observers(evt);
  }

protected:
  void addSuperObserver(std::shared_ptr< Observer<EV> > observer)
  {
    add_to_vec_uniquely(m_super_observers, observer);
  }
  
  bool send_evt_to_observers(const EV& evt)
  {
    bool handled = false;
    for (std::shared_ptr< Observer<EV> > observer : m_observers)
    {
      if (observer)
	handled |= observer->handleEvent(evt);
    }

    for (std::shared_ptr< Observer<EV> > observer : m_super_observers)
    {
      if (observer)
	handled |= observer->handleEvent(evt);
    }

    return handled;
  }
private:
  std::vector< std::shared_ptr< Observer<EV> > > m_observers;
  std::vector< std::shared_ptr< Observer<EV> > > m_super_observers;
};

} // namespace wl

#endif // EVENT_EMITTER_HPP
