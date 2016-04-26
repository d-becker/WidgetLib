#ifndef SELECTABLE_HPP
#define SELECTABLE_HPP

#include <graphics.hpp>

#include "Label.hpp"
#include "SelectionEvent.hpp"
#include "SelectionObserver.hpp"
#include "Selector.hpp"

namespace wl {

class Selectable : public Label, public Selector
{
public:
  Selectable(Vec2 position = Vec2(0, 0),
	     int width = 50,
	     int height = 50,
	     std::string text = "Selectable");

  virtual ~Selectable();

  genv::color getNormalBackgroundColour() const;
  void setNormalBackgroundColour(genv::color colour);

  genv::color getSelectedBackgroundColour() const;
  void setSelectedBackgroundColour(genv::color colour);

  genv::color getNormalTextColour() const;
  void setNormalTextColour(genv::color colour);

  genv::color getSelectedTextColour() const;
  void setSelectedTextColour(genv::color colour);

private:
  void set_normal_colours();
  void set_selected_colours();
  
  genv::color m_normal_bg;
  genv::color m_selected_bg;
  genv::color m_normal_text;
  genv::color m_selected_text;
};

} // namespace wl

#endif // SELECTABLE_HPP
