#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <memory>

#include <graphics.hpp>

#include "Box.hpp"
#include "Vec2.hpp"


namespace wl {

class Container;

/**
 * The base class for all widgets in the library. The position of the widget is
 * the position of the upper left corner of the bounding box, relative
 * to the position of the parent widget.
 */
class Widget
{
public:
  Widget(std::shared_ptr<Container> parent,
	 Vec2 position = Vec2(0, 0),
	 int width = 0,
	 int height = 0)
    : m_parent(parent),
      m_position(position),
      m_width(width),
      m_height(height)
  {
  }
  
  virtual ~Widget()
  {
  }

  /**
   * Returns a (smart) pointer to the parent widget of this widget.
   *
   * \return A (smart) pointer to the parent widget of this widget.
   */
  std::shared_ptr<Container> getParent()
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
   * with absolute (window) coordinates.
   *
   * \return The bounding box of this \c Widget as a \c Box object,
   *         with absolute (window) coordinates.
   */
  Box getBoundingBox() const
  {
    Vec2 abs_pos = getAbsPosition();
    return Box(abs_pos, abs_pos + Vec2(m_width, m_height));
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
   * Handles an event.
   *
   * \param evt The event to handle.
   */
  virtual void handleEvent(const genv::event& evt) = 0;

  /**
   * Paints the widget.
   */
  virtual void paint() const = 0;

private:
  const std::shared_ptr<Container> m_parent;
  
  Vec2 m_position;
  int m_width;
  int m_height;
};

} // namespace wl

#endif // WIDGET_HPP
