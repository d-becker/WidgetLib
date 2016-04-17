#ifndef LAYOUT_MANAGER_HPP
#define LAYOUT_MANAGER_HPP

namespace wl {

class Container;

class LayoutManager
{
public:
  /**
   * Lays out the children of the provided container.
   *
   * \param container The container whose children will be laid out.
   */
  virtual void layOutContainer(Container& container) = 0;
};

} // namespace wl

#endif // LAYOUT_MANAGER_HPP
