#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include "WidgetLib/Widget.hpp"

#include "WidgetLib/EventEmitter.hpp"
#include "WidgetLib/evt/SelectionEvent.hpp"

namespace wl {

/**
 * An abstract base class for checkboxes and radio buttons.
 */
class Selector : public Widget, public EventEmitter<SelectionEvent>
{
public:
  Selector(Vec2 position,
	   int width,
	   int height);

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
  
protected:
private:
  bool m_selected;
};

} // namespace wl

#endif // SELECTOR_HPP
