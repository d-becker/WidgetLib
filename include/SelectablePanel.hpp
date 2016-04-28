#ifndef SELECTABLE_PANEL_HPP
#define SELECTABLE_PANEL_HPP

#include <string>
#include <vector>

#include "Container.hpp"
#include "Selectable.hpp"

namespace wl {

/**
 * A panel that contains \c Selectable objects and displays them vertically.
 */
class SelectablePanel : public Container,
			//public EventEmitter<SelectionEvent>
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
  bool removeElementByText(std::string text);

  virtual void layOutChildren() override;
  virtual void paint() override;

private:
  Selectable *find_selectable_with_text(const std::string& text);
  
  std::vector<Selectable*> m_elems;
  unsigned int m_first_to_display; // The index of the first child to display
};

} // namespace wl

#endif // SELECTABLE_PANEL_HPP
