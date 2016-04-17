#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>

#include <graphics.hpp>

#include "LayoutManager.hpp"
#include "Widget.hpp"

namespace wl {

class LayoutManager;

class Container : public Widget
{
public:
  Container(Container *parent,
	    Vec2 position = Vec2(0, 0),
	    int width = 0,
	    int height = 0,
	    std::shared_ptr<LayoutManager> layout_manager = nullptr);
  
  virtual ~Container();

  /**
   * Adds the given child to this container if it is not already a child and
   * the child's parent is this container. This method should not be used
   * directly, it will be used when passing this container to the constructor
   * of the child widget.
   *
   * \param child The widget to add as a child.
   *
   * \return \c true if the child was added; \c false otherwise (also when
   *         \a child is null.
   */
  bool addChild(Widget *child);

  /**
   * Removes the given child if it is a child of this container.
   *
   * \param child The child to remove.
   *
   * \return \c true if the given widget was a child of this container
   *         and it was removed; \c false otherwise.
   */
  bool removeChild(Widget *child);

  /**
   * Returns a vector containing pointers to the children
   * of this container.
   *
   * \return A vector containing pointers to the children
   *         of this container.
   */
  const std::vector<Widget*>& getChildren() const;

  /**
   * Returns the current background colour of this container as a
   * genv::color object.
   *
   * \return The current background colour of this container.
   */
  genv::color getBackgroundColour() const;

  /**
   * Sets the background colour of this container.
   *
   * \param red The red component of the new background colour.
   * \param green The green component of the new background colour.
   * \param blue The blue component of the new background colour.
   */
  void setBackgroundColour(int red,
			   int green,
			   int blue);

  /**
   * Sets the background colour of this container.
   *
   * \param colour The new background colour.
   */
  void setBackgroundColour(genv::color colour);

  /**
   * Returns a (smart) pointer to the layout manager associated with
   * this container.
   *
   * \return A (smart) pointer to the layout manager associated with
   *         this container.
   */
  std::shared_ptr<LayoutManager> getLayoutManager() const;

  /**
   * Sets the layout manager associated with this container.
   *
   * \param layout_manager The new layout manager.
   */
  void setLayoutManager(std::shared_ptr<LayoutManager> layout_manager);

  /**
   * Calls the layout manager to lay out the children of this container. If there is no layout manager, this method does nothing.
   */
  void layOutChildren();

  
  virtual Widget* getWidgetAtPos(const Vec2& pos) override;

  virtual void paint() override;
private:
  std::vector<Widget*> m_children;

  std::shared_ptr<LayoutManager> m_layout_manager;

  genv::color m_background_colour;
};

} // namespace wl

#endif // CONTAINER_HPP
