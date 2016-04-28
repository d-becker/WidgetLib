#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <memory>

#include "ButtonEvent.hpp"
#include "ButtonObserver.hpp"
#include "EventEmitter.hpp"
#include "MouseEvent.hpp"
#include "Widget.hpp"

#include <memory>
#include <functional>
#include <vector>

namespace wl {

class Button : public Widget, public EventEmitter<ButtonEvent>
{
public:
  Button(Vec2 position = Vec2(0, 0),
	 int width = 50,
	 int height = 50);

  virtual ~Button();
  
  virtual void paint() override;

protected:
private:
};

} // namespace wl

#endif // BUTTON_HPP
