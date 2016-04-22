#include "Button.hpp"



#include <graphics.hpp>

#include "MouseObserver.hpp"
#include "MouseObserverAdapter.hpp"
#include "Util.hpp"

namespace wl {

Button::Button(Vec2 position,
	       int width,
	       int height
	       )
  : Widget(position, width, height)
{
  addMouseSuperObserver(std::make_shared<MouseObserverAdapter>([this](const MouseEvent& evt) {
	if (evt.getEvtType() == MouseEvent::CLICKED_ON_WIDGET
	    && evt.getMouseButton() == MouseEvent::MOUSE_BTN::LEFT)
	{
	  ButtonEvent button_event(this);
	  fireButtonEvent(button_event);
	  return true;
	}

	return false;
      }));
}

Button::~Button()
{
}

void Button::addButtonObserver(std::shared_ptr<ButtonObserver> observer)
{
  add_to_vec_uniquely(m_observers, observer);
}

void Button::removeButtonObserver(std::shared_ptr<ButtonObserver> observer)
{
  remove_from_vec(m_observers, observer);
}

void Button::fireButtonEvent(const ButtonEvent& evt)
{
  send_button_evt_to_observers(evt);
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

// Protected
bool Button::send_button_evt_to_observers(const ButtonEvent& evt)
{
  bool handled = false;
  for (std::shared_ptr<ButtonObserver> observer : m_observers)
  {
    if (observer)
      handled |= observer->handleButtonEvent(evt);
  }

  return handled;
}

} // namespace wl
