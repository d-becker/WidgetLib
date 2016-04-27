#ifndef SELECTABLE_PANEL_HPP
#define SELECTABLE_PANEL_HPP

#include <string>
#include <vector>

#include "Container.hpp"
#include "Selectable.hpp"

namespace wl {

/**
 * A panel that contains \c Selectable objects and displays them vertically.
 * It resizes itself to accomodate all children upon adding/removing them.
 */
class SelectablePanel : public Container
{
public:
  SelectablePanel(Vec2 position = Vec2(0, 0),
		  int width = 50,
		  int height = 50,
		  const std::vector<Selectable*>& elems = {});
  virtual ~SelectablePanel();

  const std::vector<Selectable*> getElements() const;

  bool addElement(Selectable *elem);
  bool removeElement(Selectable *elem);

  virtual void layOutChildren() override;

private:
  bool add_elem_without_resize(Selectable *elem);
  void adjust_size();

  // The new size calculated from the child widgets
  void get_new_size(int& new_width, int& new_height) const;
  int get_max_child_width() const;
  int get_sum_child_height() const;
  
  std::vector<Selectable*> m_elems;
};

} // namespace wl

#endif // SELECTABLE_PANEL_HPP
