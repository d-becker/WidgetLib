#ifndef RADIO_BUTTON_HPP
#define RADIO_BUTTON_HPP

#include "WidgetLib/Selector.hpp"

#include <memory>

namespace wl {

class RadioButton : public Selector
{
public:
  RadioButton(Vec2 position,
	      int width,
	      int height);

  virtual ~RadioButton();

  virtual void paint() override;

private:
  int m_inset;
};

} // namespace wl

#endif // RADIO_BUTTON_HPP
