#include "RadioButton.hpp"

#include <cmath>

#include "evt/MouseEvent.hpp"
#include "evt/ObserverAdapter.hpp"

namespace wl {

RadioButton::RadioButton(Vec2 position,
			 int width,
			 int height)
  : Selector(position, width, height),
    m_inset(2)
{
  // Background colour
  setBackgroundColour(192,192,192);
  
  // Super observers
  addMouseSuperObserver(std::make_shared< ObserverAdapter<MouseEvent> >([this](const MouseEvent& evt) {
	if (evt.getEvtType() == MouseEvent::CLICKED_ON_WIDGET)
	{
	  select();
	  return true;
	}

	return false;
      }));
}

RadioButton::~RadioButton()
{
}

void RadioButton::paint()
{
  using namespace genv;

  auto canv_ptr = getCanvas();
  if (!canv_ptr)
    return;

  canvas& canv = *canv_ptr;
  
  int width = getWidth();
  int height = getHeight();
  int available_width = width - 2 * m_inset;
  int available_height = height - 2 * m_inset;
  int diameter = std::min(available_width, available_height);
  int radius = diameter / 2;

  // Background
  canv << getBackgroundColour()
       << move_to(0, 0)
       << box(width, height);

  // Black circumference
  canv << color(0, 0, 0); // not transparent but still black

  int center_x = (available_width - diameter) / 2 + radius + m_inset;
  int center_y = (available_height - diameter) / 2 + radius + m_inset;
  
  for (double i = -radius; i <= radius; ++i)
  {
    for (double j = -radius; j <= radius; ++j)
    {
      if (i * i + j * j <= radius * radius)
      {
	canv << move_to(center_x + i, center_y + j) << dot;
      }
    }
  }

  // White inside
  int w_diameter = diameter * 0.8;
  int w_radius = w_diameter / 2;
  canv << color(255, 255, 255);
  for (double i = -w_radius; i <= w_radius; ++i)
  {
    for (double j = -w_radius; j <= w_radius; ++j)
    {
      if (i * i + j * j <= w_radius * w_radius)
      {
	canv << move_to(center_x + i, center_y + j) << dot;
      }
    }
  }

  // Black if selected
  if (isSelected())
  {
    int s_diameter = diameter * 0.5;
    int s_radius = s_diameter / 2;
    canv << color(0, 0, 0);
    for (double i = -s_radius; i <= s_radius; ++i)
    {
      for (double j = -s_radius; j <= s_radius; ++j)
      {
	if (i * i + j * j <= s_radius * s_radius)
	{
	  canv << move_to(center_x + i, center_y + j) << dot;
	}
      }
    }
  }
}

} // namespace wl
