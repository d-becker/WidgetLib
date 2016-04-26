#ifndef SELECTABLE_HPP
#define SELECTABLE_HPP

#include <graphics.hpp>

#include "Label.hpp"

namespace wl {

class Selectable : public Label
{
public:
  Selectable(Vec2 position = Vec2(0, 0),
	     int width = 50,
	     int height = 50,
	     std::string text = "Selectable");

  virtual ~Selectable();

  bool isSelected() const;
  void select();
  void deselect();

  genv::color getNormalBackgroundColour() const;
  void setNormalBackgroundColour(genv::color colour);

  genv::color getSelectedBackgroundColour() const;
  void setSelectedBackgroundColour(genv::color colour);

  genv::color getNormalTextColour() const;
  void setNormalTextColour(genv::color colour);

  genv::color getSelectedTextColour() const;
  void setSelectedTextColour(genv::color colour);

private:
  bool m_selected;
  
  genv::color m_normal_bg;
  genv::color m_selected_bg;
  genv::color m_normal_text;
  genv::color m_selected_text;
};

} // namespace wl

#endif // SELECTABLE_HPP
