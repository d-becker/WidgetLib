#include "Checkbox.hpp"

#include "Util.hpp"

#include "CheckboxObserverAdapter.hpp"
#include "MouseObserverAdapter.hpp"

namespace wl {

Checkbox::Checkbox(Vec2 position,
		   int width,
		   int height)
  : Selector(position, width, height)
{
  // Background colour
  setBackgroundColour(255, 255, 255);

  // Super observers
  addMouseSuperObserver(std::make_shared<MouseObserverAdapter>([this](const MouseEvent& evt) {
	if (evt.getEvtType() == MouseEvent::CLICKED_ON_WIDGET)
	{
	  toggle();
	  return true;
	}

	return false;
      }));
}

Checkbox::~Checkbox()
{
}

void Checkbox::paint()
{
  using namespace genv;
  
  // TODO.
  int width = getWidth();
  int height = getHeight();

  auto canv_ptr = getCanvas();

  if (!canv_ptr)
    return;

  canvas& canv = *canv_ptr;

  // Background
  canv << getBackgroundColour()
       << move_to(0, 0)
       << box(width, height);
  
  // Edges
  canv << color(0, 0, 0)
       << move_to(0, 0)
       << line(width, 0)
       << line(0, height)
       << line(-width, 0)
       << line(0, -height);

  // Cross
  if (isSet())
  {
    canv << move_to(0, 0)
         << line(width, height)
         << move_to(width - 1, 0)
         << line(-width, height);
  }
}

}
