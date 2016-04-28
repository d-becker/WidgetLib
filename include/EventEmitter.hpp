#ifndef EVENT_EMITTER_HPP
#define EVENT_EMITTER_HPP

#include <memory>
#include <vector>

#include "Observer.hpp"
#include "Util.hpp"
#include "Widget.hpp"

namespace wl {

class Widget;

/**
 * A class that handles registering observers and firing events. The template
 * parameter \a EV should be the type of event whose observers
 * this class handles.
 * This class should never be instantiated on its own and should only be
 * subclassed by classes that also derive from <tt>Widget</tt>. The first
 * parameter of the constructor (the \c Widget pointer) should be a pointer to
 * this object as a <tt>Widget</tt>. Otherwise, the behaviour is undefined.
 *
 * \param EV The type of event whose observers this class handles.
 */
template <typename EV>
class EventEmitter
{
public:
  /**
   * Constructs a new \c EventEmitter object.
   *
   * \param this_widget A pointer to this object as a <tt>Widget</tt>
   *        (see the class documentation for more information).
   * \param propagate Should be \c true if the events emitted should propagate
   *        upwards to the parent if they are not fully handled.
   */
  EventEmitter(Widget *this_widget,
	       bool propagate)
    : m_this_widget(this_widget),
      m_propagate(propagate)
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
   *//*
  void fireEvent(const EV& evt)
  {
    bool handled = send_selection_evt_to_observers(evt);
    if (m_propagate && !handled && m_this_widget)
    {
      auto parent = m_this_widget->getParent();
      if (parent)
	parent->fireEvent(evt);
    }
  }*/

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

  bool m_propagate; // True if the event should propagate upwards to the parent
		    // if it is not fully handled

  Widget *m_this_widget; // A pointer to this object as a \c Widget
};

} // namespace wl

#endif // EVENT_EMITTER_HPP
