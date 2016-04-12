#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <memory>
#include <vector>

#include <graphics.hpp>

#include "Box.hpp"
#include "MouseObserver.hpp"
#include "Vec2.hpp"


namespace wl {

class Container;
class MouseEvent;

/**
 * The base class for all widgets in the library. The position of the widget is
 * the position of the upper left corner of the bounding box, relative
 * to the position of the parent widget.
 */
class Widget
{
public:
  Widget(Container *parent,
	 Vec2 position = Vec2(0, 0),
	 int width = 0,
	 int height = 0);
  
  virtual ~Widget()
  {
  }

  /**
   * Returns a pointer to the parent widget of this widget.
   *
   * \return A pointer to the parent widget of this widget.
   */
  Container *getParent()
  {
    return m_parent;
  }

  /**
   * Returns the position of the upper left corner of the bounding box of
   * this \c Widget in relative coordinates (relative to the position of
   * the parent).
   *
   * \return The position of the upper left corner of the bounding box of
   *         this \c Widget.
   */
  Vec2 getPosition() const
  {
    return m_position;
  }

  /**
   * Returns the position of the upper left corner of the bounding box of this
   * \c Widget in absolute (window) coordinates.
   *
   * \return The position of the upper left corner of the bounding box of this
   *         \c Widget in absolute (window) coordinates.
   */
  Vec2 getAbsPosition() const; // Defined in cpp to be able to use the
			       // class Container.
  
  /**
   * Returns the bounding box of this \c Widget as a \c Box object,
   * in coordinates relative to the parent.
   *
   * \return The bounding box of this \c Widget as a \c Box object,
   *         in coordinates relative to the parent.
   */
  Box getBoundingBox() const
  {
    return Box(m_position, m_position + Vec2(m_width, m_height));
  }

  /**
   * Returns the width of this \c Widget.
   *
   * \return The width of this \c Widget.
   */
  int getWidth() const
  {
    return m_width;
  }

  /**
   * Returns the height of this \c Widget.
   *
   * \return The height of this \c Widget.
   */  
  int getHeight() const
  {
    return m_height;
  }

  /**
   * Sets the position of this \c Widget to the specified position.
   *
   * \param pos The new position of the \c Widget.
   */
  void setPosition(const Vec2& pos)
  {
    m_position = pos;
  }

  /**
   * Sets the position of this \c Widget to the specified position.
   *
   * \param x The x coordinate of the new position.
   * \param y The y coordinate of the new position.
   */
  void setPosition(int x, int y)
  {
    setPosition(Vec2(x, y));
  }

  /**
   * Sets the width of this \c Widget to the specified value if that is not
   * negative. If the specified value is negative, nothing is done.
   *
   * \param w The new width of the widget.
   */
  void setWidth(int w)
  {
    if (w >= 0)
      m_width = w;
  }

  /**
   * Sets the height of this \c Widget to the specified value if that is not
   * negative. If the specified value is negative, nothing is done.
   *
   * \param hw The new height of the widget.
   */
  void setHeight(int h)
  {
    if (h >= 0)
      m_height = h;
  }

  /**
   * Returns \c true if the given point is inside the area of the widget.
   * The point's coordinates are interpreted as if in absolute (window)
   * coordinates.
   *
   * \param point The point in absolute (window) coordinates that is checked.
   *
   * \return \c true if the given point is inside the area of the widget;
   *         \c false otherwise.
   */
  bool isInside(const Vec2& point)
  {
    return getBoundingBox().isInside(point);
  }

  /**
   * If this is a container widget, returns the child widget that is under the
   * given position. The position is interpreted as given by the coordinate
   * system relative to the position of this widget. If there is no widget under
   * the given position, returns a null pointer.
   * If this widget is not a container, this method returns this widget or a
   * null pointer if the given position is not inside the area if this widget.
   *
   * \param pos The position in the coordinate system of this widget that will
   *            be checked.
   *
   * \return The child widget at the given position if this is a container
   *         widget, this widget if this is not a container or \c nullptr
   *         if there is no widget at the given position.
   */
  virtual Widget *getWidgetAtPos(const Vec2& pos)
  {
    // Default implementation for non-container widgets.
    if (isInside(pos + m_position))
      return this;
    else
      return nullptr;
  }

  const std::vector< std::shared_ptr<MouseObserver> > getMouseObservers() const
  {
    return m_mouse_observers;
  }

  /**
   * Subsribes a mouse observer (if the same observer is not already subscribed)
   * to this widget. The observer will be notified when a \c MouseEvent is
   * fired by this widget.
   *
   * \param observer The observer to subscribe.
   */
  void addMouseObserver(std::shared_ptr<MouseObserver> observer);

  /**
   * Unsubscribes the \c MouseObserver with the given index if it exists.
   * This method does nothing if the element with index \a index does not exist.
   *
   * \param index The index of the \c MouseObserver to unsubscribe.
   */
  void removeMouseObserver(unsigned int index);

  /**
   * Unsubscribes the provided \c MouseObserver if is subscribed to this widget.
   * This method does nothing if provided \c MouseObserver is not subscribed to
   * this widget.
   *
   * \param observer The \c MouseObserver to unsubscribe.
   */
  void removeMouseObserver(std::shared_ptr<MouseObserver> observer);

  /**
   * If a mouse event happens over this widget, the \c Toplevel that created
   * the event communicates it to the widget with this method. This method then
   * notifies all the observers that are subscribed for this event.
   *
   * \param evt The event to fire.
   */
  void fireMouseEvent(const MouseEvent& evt);


  /**
   * Paints the widget.
   */
  virtual void paint() const = 0;

private:
  Container *m_parent;
  
  Vec2 m_position;
  int m_width;
  int m_height;

  std::vector< std::shared_ptr<MouseObserver> > m_mouse_observers;
};

} // namespace wl

#endif // WIDGET_HPP
