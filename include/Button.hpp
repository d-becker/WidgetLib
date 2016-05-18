#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <memory>

#include "EventEmitter.hpp"
#include "evt/ButtonEvent.hpp"
#include "evt/MouseEvent.hpp"
#include "Widget.hpp"

#include <memory>
#include <functional>
#include <vector>

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
