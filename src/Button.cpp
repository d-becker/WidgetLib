#include "Button.hpp"

#include <graphics.hpp>

#include "evt/ObserverAdapter.hpp"
#include "Util.hpp"

namespace wl {

Button::Button(Vec2 position,
	       int width,
	       int height
	       )
  : Widget(position, width, height)
{
  addMouseSuperObserver(std::make_shared< ObserverAdapter<MouseEvent> >([this](const MouseEvent& evt) {
	if (evt.getEvtType() == MouseEvent::CLICKED_ON_WIDGET
	    && evt.getMouseButton() == MouseEvent::MOUSE_BTN::LEFT)
	{
	  ButtonEvent button_event(this);
	  fireEvent(button_event);
	  return true;
	}

	return false;
      }));
}

Button::~Button()
{
}

void Button::paint()
{
  // Testing
  using namespace genv;
  canvas& c = *getCanvas();
  c << move_to(0, 0);
  c << color(0, 0, 255);
  c << box(getWidth(), getHeight());
}

} // namespace wl
