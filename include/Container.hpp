#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>

#include <graphics.hpp>

#include "Widget.hpp"

namespace wl {

class LayoutManager;

class Container : public Widget
{
public:
  Container(Vec2 position,
	    int width,
	    int height);
  
  virtual ~Container();

  /**
   * Returns a vector containing pointers to the children
   * of this container.
   *
   * \return A vector containing pointers to the children
   *         of this container.
   */
  const std::vector<Widget*>& getChildren() const;

  virtual Widget* getWidgetAtPos(const Vec2& pos) override;

  virtual void paint() override;

  /**
   * Lay out the children of this container.
   */
  virtual void layOutChildren() = 0;

protected:
  /**
   * Adds the given child to this container if it is not already a child of
   * this or another container and is not nullptr.
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
private:
  std::vector<Widget*> m_children;
};

} // namespace wl

#endif // CONTAINER_HPP
