#ifndef FREE_PANEL_HPP
#define FREE_PANEL_HPP

#include "WidgetLib/Container.hpp"

namespace wl {

/**
 * A container with no layout management, the children are placed according to
 * their position.
 */
class FreePanel : public Container
{
public:
  FreePanel(Vec2 position,
	    int width,
	    int height);

  virtual ~FreePanel();

   /**
   * Adds the given child to this \c FreePanel if it is not already a child of
   * this or another container and is not nullptr.
   *
   * \param child The widget to add as a child.
   *
   * \return \c true if the child was added; \c false otherwise (also when
   *         \a child is null.
   */
  bool addChild(Widget *child);

   /**
   * Removes the given child if it is a child of this \c FreePanel.
   *
   * \param child The child to remove.
   *
   * \return \c true if the given widget was a child of this \c FreePanel
   *         and it was removed; \c false otherwise.
   */
  bool removeChild(Widget *child);

  virtual void layOutChildren() override;
};

} // namespace wl

#endif // FREE_PANEL_HPP
