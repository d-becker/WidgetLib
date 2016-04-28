#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <memory>
#include <vector>

#include <graphics.hpp>

#include "Box.hpp"
#include "EventEmitter.hpp"
#include "FocusEvent.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"
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
class Widget : public EventEmitter<FocusEvent>,
	       public EventEmitter<KeyEvent>,
	       public EventEmitter<MouseEvent>,
	       public EventEmitter<ResizeEvent>
	       
{
  friend class Container;
public:
  Widget(Vec2 position = Vec2(0, 0),
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

  /**
   * The widgets that handle observers derive from \c EventEmitter<T>. In the
   * \c fireEvent(const T& evt) method of that class, the event can be
   * propagated to the parent by calling the \c fireEvent(const T& evt) method
   * of the parent, but it is possible that the parent does not derive from
   * \c EventEmitter<T>. To avoid the compiler error, this generic default
   * method is supplied. This method does nothing.
   */
  template <typename T>
  void fireEvent(const T& ev)
  {
    // Does nothing.
  }
  
  void stampCanvas(genv::canvas& on_which,
		   int x,
		   int y) const
  {
    if (m_canvas)
      on_which << genv::stamp(*m_canvas, x, y);
  }

  /**
   * Returns the current background colour of this widget as a
   * genv::color object.
   *
   * \return The current background colour of this container.
   */
  genv::color getBackgroundColour() const;

  /**
   * Sets the background colour of this widget.
   *
   * \param red The red component of the new background colour.
   * \param green The green component of the new background colour.
   * \param blue The blue component of the new background colour.
   */
  void setBackgroundColour(int red,
			   int green,
			   int blue);

  /**
   * Sets the background colour of this widget.
   *
   * \param colour The new background colour.
   */
  void setBackgroundColour(genv::color colour);

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

  // Registering super observers - they cannot be deleted or added from outside
  void addMouseSuperObserver(std::shared_ptr<MouseObserver> observer);
  void addKeySuperObserver(std::shared_ptr<KeyObserver> observer);
  void addResizeSuperObserver(std::shared_ptr<ResizeObserver> observer);
  void addFocusSuperObserver(std::shared_ptr<FocusObserver> observer);

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

  // Used by the friend class Container
  void set_parent(Container *parent);
  
  // Observers
  std::vector< std::shared_ptr<MouseObserver> > m_mouse_observers;
  std::vector< std::shared_ptr<KeyObserver> > m_key_observers;
  std::vector< std::shared_ptr<ResizeObserver> > m_resize_observers;
  std::vector< std::shared_ptr<FocusObserver> > m_focus_observers;

  // Super observers - they cannot be deleted from outside, by public methods
  std::vector< std::shared_ptr<MouseObserver> > m_mouse_super_observers;
  std::vector< std::shared_ptr<KeyObserver> > m_key_super_observers;
  std::vector< std::shared_ptr<ResizeObserver> > m_resize_super_observers;
  std::vector< std::shared_ptr<FocusObserver> > m_focus_super_observers;

  std::shared_ptr<genv::canvas> m_canvas;

  // Backgound colour
  genv::color m_background_colour;
};

} // namespace wl

#endif // WIDGET_HPP
