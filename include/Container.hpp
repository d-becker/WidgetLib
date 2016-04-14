#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>

#include "Widget.hpp"

namespace wl {

class Container : public Widget
{
public:
  Container(Container *parent,
	    Vec2 position = Vec2(0, 0),
	    int width = 0,
	    int height = 0);
  
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

  
  virtual Widget* getWidgetAtPos(const Vec2& pos) override;

  virtual void paint() const override;
private:
  std::vector<Widget*> m_children;
};

} // namespace wl

#endif // CONTAINER_HPP
