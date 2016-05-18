#include "Checkbox.hpp"

#include "EventEmitter.hpp"
#include "evt/MouseEvent.hpp"
#include "evt/ObserverAdapter.hpp"
#include "Util.hpp"

namespace wl {

Checkbox::Checkbox(Vec2 position,
		   int width,
		   int height)
  : Selector(position, width, height)
{
  // Background colour
  setBackgroundColour(255, 255, 255);

  // Super observers
  addMouseSuperObserver(std::make_shared< ObserverAdapter<MouseEvent> >(
					 [this](const MouseEvent& evt) {
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

  auto canv_ptr = getCanvas();
  if (!canv_ptr)
    return;

  canvas& canv = *canv_ptr;
  
  int width = getWidth();
  int height = getHeight();

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
  if (isSelected())
  {
    canv << move_to(0, 0)
         << line(width, height)
         << move_to(width - 1, 0)
         << line(-width, height);
  }
}

}
