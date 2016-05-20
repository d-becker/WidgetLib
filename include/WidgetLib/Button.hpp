#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <memory>
#include <functional>
#include <vector>

#include "WidgetLib/EventEmitter.hpp"
#include "WidgetLib/evt/ButtonEvent.hpp"
#include "WidgetLib/evt/MouseEvent.hpp"
#include "WidgetLib/Widget.hpp"

namespace wl {

class Button : public Widget, public EventEmitter<ButtonEvent>
{
public:
  Button(Vec2 position,
	 int width,
	 int height);

  virtual ~Button();
  
  virtual void paint() override;

protected:
private:
};

} // namespace wl

#endif // BUTTON_HPP
