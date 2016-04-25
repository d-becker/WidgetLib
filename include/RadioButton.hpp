#ifndef RADIO_BUTTON_HPP
#define RADIO_BUTTON_HPP

#include "Selector.hpp"

#include <memory>

namespace wl {

class RadioButton : public Selector
{
public:
  RadioButton(Vec2 position = Vec2(0, 0),
	      int width = 50,
	      int height = 50);

  virtual ~RadioButton();

  virtual void paint() override;

private:
  int m_inset;
};

} // namespace wl

#endif // RADIO_BUTTON_HPP
