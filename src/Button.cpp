#include "Button.hpp"

#include <graphics.hpp>

#include "MouseObserver.hpp"
#include "MouseObserverAdapter.hpp"

namespace wl {

Button::Button(Container *parent,
	       Vec2 position,
	       int width,
	       int height,
	       std::function<bool(const MouseEvent&)> callback
	       )
  : Widget(parent, position, width, height),
    m_callback(callback)
{
  std::shared_ptr<MouseObserver> observer =
    std::make_shared<MouseObserverAdapter>([this](const MouseEvent& evt) {
	if (evt.getEvtType() == MouseEvent::CLICKED_ON_WIDGET && m_callback)
	  return m_callback(evt);
	else
	  return false;
    });
  addMouseObserver(observer);
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
