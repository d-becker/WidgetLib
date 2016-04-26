#ifndef SELECTABLE_PANEL_HPP
#define SELECTABLE_PANEL_HPP

#include <string>
#include <vector>

#include "Container.hpp"
#include "Selectable.hpp"

namespace wl {

class SelectablePanel : public Container
{
public:
  SelectablePanel(Vec2 position = Vec2(0, 0),
		  int width = 50,
		  int height = 50,
		  std::vector<Selectable*> elems = {});
  virtual ~SelectablePanel();

  const std::vector<Selectable*> getElements() const;

  bool addElement(Selectable *elem);
  bool removeElement(Selectable *elem);

private:
  std::vector<Selectable*> m_elems;
};

} // namespace wl

#endif // SELECTABLE_PANEL_HPP
