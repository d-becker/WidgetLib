#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <memory>
#include <vector>

#include <graphics.hpp>

#include "Box.hpp"
#include "ResizeEvent.hpp"
#include "Vec2.hpp"


namespace wl {

class Container;
class FocusEvent;
class FocusObserver;
class KeyEvent;
class KeyObserver;
class MouseEvent;
class MouseObserver;
class ResizeObserver;
class Toplevel;

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
  
  virtual ~Widget();

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
    {
      m_width = w;
      getNewCanvas();
      fireResizeEvent(ResizeEvent(this, m_width, m_height));
    }
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
    {
      m_height = h;
      getNewCanvas();
      fireResizeEvent(ResizeEvent(this, m_width, m_height));
    }
  }

  /**
   * Sets the site of this \c Widget to  the specified values
   * if those are not negative. If at least one of the values is negative,
   * nothing is done.
   *
   * \param width The new width of the widget.
   * \param height The new height of the widget.
   */
  void setSize(int width,
	       int height)
  {
    if (width >= 0 && height >= 0)
    {
      m_width = width;
      m_height = height;

      getNewCanvas();
      fireResizeEvent(ResizeEvent(this, m_width, m_height));
    }
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
   * given position. The position is interpreted in the coordinate
   * system relative to the position of this widget. If there is no widget at
   * the given position, or if this is not a container, returns a \c this.
   *
   * Note: this method should not normally be overridden.
   *
   * \param pos The position in the coordinate system of this widget that will
   *            be checked.
   *
   * \return The child widget at the given position if this is a container
   *         widget, this widget if there is no child widget at the given
   *         position or if this is not a container.
   */
  virtual Widget *getWidgetAtPos(const Vec2& pos)
  {
    // Default implementation for non-container widgets.
    return this;
  }

  /**
   * Returns the \c Toplevel object that this widget is a descendant of.
   *
   * Note: this method should not normally be overridden.
   *
   * \return The \c Toplevel object that this widget is a descendant of.
   */
  virtual Toplevel *getToplevel();

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
   * Unsubscribes the provided \c MouseObserver if it is subscribed to this widget.
   * This method does nothing if provided \c MouseObserver is not subscribed to
   * this widget.
   *
   * \param observer The \c MouseObserver to unsubscribe.
   */
  void removeMouseObserver(std::shared_ptr<MouseObserver> observer);

  /**
   * If a mouse event happens over this widget, the \c Toplevel that created
   * the event communicates it to the widget with this method. This method then
   * notifies all the observers that are subscribed to this event.
   *
   * \param evt The event to fire.
   */
  void fireMouseEvent(const MouseEvent& evt);

  /**
   * Subsribes a key observer (if the same observer is not already subscribed)
   * to this widget. The observer will be notified when a \c KeyEvent is
   * fired by this widget.
   *
   * \param observer The observer to subscribe.
   */
  void addKeyObserver(std::shared_ptr<KeyObserver> observer);

  /**
   * Unsubscribes the \c KeyObserver with the given index if it exists.
   * This method does nothing if the element with index \a index does not exist.
   *
   * \param index The index of the \c KeyObserver to unsubscribe.
   */
  void removeKeyObserver(unsigned int index);
  
  /**
   * Unsubscribes the provided \c KeyObserver if it is subscribed to this widget.
   * This method does nothing if provided \c KeyObserver is not subscribed to
   * this widget.
   *
   * \param observer The \c KeyObserver to unsubscribe.
   */
  void removeKeyObserver(std::shared_ptr<KeyObserver> observer);
  
  /**
   * If a key event happens over this widget, the \c Toplevel that created
   * the event communicates it to the widget with this method. This method then
   * notifies all the observers that are subscribed to this event.
   *
   * \param evt The event to fire.
   */
  void fireKeyEvent(const KeyEvent& evt);

   /**
   * Subsribes a resize observer (if the same observer is not already
   * subscribed) to this widget. The observer will be notified when a
   * \c ResizeEvent is fired by this widget.
   *
   * \param observer The observer to subscribe.
   */
  void addResizeObserver(std::shared_ptr<ResizeObserver> observer);

  /**
   * Unsubscribes the \c ResizeObserver with the given index if it exists.
   * This method does nothing if the element with index \a index does not exist.
   *
   * \param index The index of the \c ResizeObserver to unsubscribe.
   */
  void removeResizeObserver(unsigned int index);
  
  /**
   * Unsubscribes the provided \c ResizeObserver if it is subscribed to
   * this widget. This method does nothing if provided \c ResizeObserver
   * is not subscribed to this widget.
   *
   * \param observer The \c ResizeObserver to unsubscribe.
   */
  void removeResizeObserver(std::shared_ptr<ResizeObserver> observer);
  
  /**
   * If this widget is resized, this method is used to notify all the observers
   * that are subscribed to this event. This method is called automatically from
   * \c setWidth, \c setHeight and \c setSize.
   *
   * \param evt The event to fire.
   */
  void fireResizeEvent(const ResizeEvent& evt);

  /**
   * Subsribes a focus observer (if the same observer is not already subscribed)
   * to this widget. The observer will be notified when a \c FocusEvent is
   * fired by this widget.
   *
   * \param observer The observer to subscribe.
   */
  void addFocusObserver(std::shared_ptr<FocusObserver> observer);

  /**
   * Unsubscribes the \c FocusObserver with the given index if it exists.
   * This method does nothing if the element with index \a index does not exist.
   *
   * \param index The index of the \c FocusObserver to unsubscribe.
   */
  void removeFocusObserver(unsigned int index);
  
  /**
   * Unsubscribes the provided \c FocusObserver if it is subscribed to this widget.
   * This method does nothing if provided \c FocusObserver is not subscribed to
   * this widget.
   *
   * \param observer The \c FocusObserver to unsubscribe.
   */
  void removeFocusObserver(std::shared_ptr<FocusObserver> observer);
  
  /**
   * If a focus event happens over this widget, the \c Toplevel that created
   * the event communicates it to the widget with this method. This method then
   * notifies all the observers that are subscribed to this event.
   *
   * \param evt The event to fire.
   */
  void fireFocusEvent(const FocusEvent& evt);

  /**
   * Grabs the focus.
   */
  void grabFocus();

  /**
   * Stamps the canvas on which this widget draws onto the given canvas. This
   * method can be used by parent (container) widgets to draw their children.
   *
   * \param on_which The canvas on which to stamp
   *        the canvas on which this widget draws.
   * \param x The x position on canvas \a on_which where this widget's canvas
   *        will be stamped.
   * \param y The y position on canvas \a on_which where this widget's canvas
   *        will be stamped.
   */
  void stampCanvas(genv::canvas& on_which,
		   int x,
		   int y) const
  {
    if (m_canvas)
      on_which << genv::stamp(*m_canvas, x, y);
  }

  /**
   * Paints the widget.
   */
  virtual void paint() = 0;

protected:
  // These methods send the events to the observers and return \c true if at
  // least one of the observers indicated that it has fully handled the event
  bool send_mouse_evt_to_observers(const MouseEvent& evt);
  bool send_key_evt_to_observers(const KeyEvent& evt);
  bool send_resize_evt_to_observers(const ResizeEvent& evt);
  bool send_focus_evt_to_observers(const FocusEvent& evt);

  // Destructs the previous canvas and creates a new one
  // with the current widget size
  void getNewCanvas();

  // Returns the canvas associated with this widget.
  std::shared_ptr<genv::canvas> getCanvas();

  // Const version of the above.
  std::shared_ptr<const genv::canvas> getCanvas() const;
private:
  Container *m_parent;
  
  Vec2 m_position;
  int m_width;
  int m_height;

  std::vector< std::shared_ptr<MouseObserver> > m_mouse_observers;
  std::vector< std::shared_ptr<KeyObserver> > m_key_observers;
  std::vector< std::shared_ptr<ResizeObserver> > m_resize_observers;
  std::vector< std::shared_ptr<FocusObserver> > m_focus_observers;

  std::shared_ptr<genv::canvas> m_canvas;
};

} // namespace wl

#endif // WIDGET_HPP
