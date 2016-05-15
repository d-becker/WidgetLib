#ifndef SELECTABLE_HPP
#define SELECTABLE_HPP

#include <graphics.hpp>

#include "EventEmitter.hpp"
#include "Label.hpp"
#include "Selector.hpp"

namespace wl {

class Selectable : public Label
{
public:
  Selectable(Vec2 position,
	     int width,
	     int height,
	     std::string text = "Selectable");

  virtual ~Selectable();

  bool isSelected() const;
  void select();
  void deselect();

  genv::color getNormalBackgroundColour() const;
  void setNormalBackgroundColour(genv::color colour);

  genv::color getSelectedBackgroundColour() const;
  void setSelectedBackgroundColour(genv::color colour);

  genv::color getNormalTextColour() const;
  void setNormalTextColour(genv::color colour);

  genv::color getSelectedTextColour() const;
  void setSelectedTextColour(genv::color colour);

  /**
   * Subscribes a selection observer (if the same observer is not already
   * subscribed) to this widget. The observer will be notified when a
   * \c SelectionEvent is fired by this widget.
   *
   * \param observer The observer to subscribe.
   */
  //void addSelectionObserver(std::shared_ptr<SelectionObserver> observer);

  /**
   * Unsubscribes the \c SelectionObserver with the given index if it exists.
   * This method does nothing if the element with index \a index does not exist.
   *
   * \param index The index of the \c SelectionObserver to unsubscribe.
   */
  //void removeSelectionObserver(std::shared_ptr<SelectionObserver> observer);

  /**
   * This method notifies all the observers that are subscribed to the
   * <tt>SelectionEvent</tt>s  events of this widget.
   *
   * \param evt The event to fire.
   */
  //void fireSelectionEvent(const SelectionEvent& evt);
  
protected:
  /*void addSelectionSuperObserver(std::shared_ptr<SelectionObserver> observer);
    bool send_selection_evt_to_observers(const SelectionEvent& evt);*/

private:
  void set_normal_colours();
  void set_selected_colours();
  
  bool m_selected;
  
  genv::color m_normal_bg;
  genv::color m_selected_bg;
  genv::color m_normal_text;
  genv::color m_selected_text;

  /*std::vector< std::shared_ptr<SelectionObserver> > m_observers;
    std::vector< std::shared_ptr<SelectionObserver> > m_super_observers;*/
};

} // namespace wl

#endif // SELECTABLE_HPP
