#include "SelectablePanel.hpp"

#include "Util.hpp"

namespace wl {

SelectablePanel::SelectablePanel(Vec2 position,
				 int width,
				 int height,
				 std::vector<Selectable*> elems)
  : Container(position, width, height),
    m_elems(elems)
{
}

SelectablePanel::~SelectablePanel()
{
}

const std::vector<Selectable*> SelectablePanel::getElements() const
{
  return m_elems;
}

bool SelectablePanel::addElement(Selectable *elem)
{
  bool added = addChild(elem);
  if (added)
    m_elems.emplace_back(elem);

  return added;
}

bool SelectablePanel::removeElement(Selectable *elem)
{
  bool removed = removeChild(elem);
  if (removed)
    remove_from_vec(m_elems, elem);

  return removed;
}

} // namespace wl
