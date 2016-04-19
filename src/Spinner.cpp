#include "Spinner.hpp"

#include <graphics.hpp>

#include "Button.hpp"
#include "Container.hpp"
#include "MouseEvent.hpp"
#include "MouseObserver.hpp"
#include "MouseObserverAdapter.hpp"
#include "TextBox.hpp"

namespace wl {

class Spinner::ArrowButton : public Button
{
public:
  enum DIRECTION
  {
    UP,
    DOWN
  };
  
  ArrowButton(Vec2 position = Vec2(0, 0),
	      int width = 50,
	      int height = 50,
	      DIRECTION dir = UP
	      )
    : Button(position, width, height),
      m_dir(dir),
      m_arrow_colour(0, 0, 0)
  {
    setBackgroundColour(192,192,192);
  }

  virtual ~ArrowButton() {}

  virtual void paint() override
  {
    using namespace genv;
    double width = getWidth();
    double height = getHeight();
    std::shared_ptr<canvas> c_ptr = getCanvas();
    if (!c_ptr)
      return;

    canvas& c = *c_ptr;

    // Clearing the canvas
    c << getBackgroundColour()
      << move_to(0, 0)
      << box(width, height);

    double x_relative_padding = 0.2; // ratio
    double y_relative_padding = 0.2; // ratio
    
    double x_start = width * x_relative_padding;
    double y_start = m_dir == UP ? height * (1 - y_relative_padding)
                                 : height * y_relative_padding;

    double y_coeff = m_dir == UP ? -1.0 : 1.0;

    // Drawing the edge
    c << move_to(0, 0)
      << m_arrow_colour
      << line(width, 0)
      << line(0, height)
      << line(-width, 0)
      << line(0, -height);

    // Drawing the arrow
    c << move_to(x_start, y_start)
      << line(width * (1 - 2 * x_relative_padding) / 2,
	      y_coeff * height * (1 - 2 * y_relative_padding))
      << line(width * (1 - 2 * x_relative_padding) / 2,
	      -y_coeff * height * (1 - 2 * y_relative_padding));
  }

  
private:
  DIRECTION m_dir;
  genv::color m_arrow_colour;
};

Spinner::Spinner(Vec2 position,
		 int width,
		 int height)
  : Container(position, width, height),
    m_text_box(new TextBox()),
    m_arrow_up(new ArrowButton(Vec2(0, 0), 0, 0, ArrowButton::UP)),
    m_arrow_down(new ArrowButton(Vec2(0, 0), 0, 0, ArrowButton::DOWN))
{
  addChild(m_text_box);
  addChild(m_arrow_up);
  addChild(m_arrow_down);

  layOutChildren();
}

Spinner::~Spinner()
{
}

void Spinner::layOutChildren()
{
  int whole_width = getWidth();
  int whole_height = getHeight();
    
  int arrow_width = whole_height;
  int arrow_height = whole_height / 2;

  m_arrow_up->setSize(arrow_width, arrow_height);
  m_arrow_down->setSize(arrow_width, arrow_height);

  m_arrow_up->setPosition(whole_width - arrow_width, 0);
  m_arrow_down->setPosition(whole_width - arrow_width, arrow_height);

  m_text_box->setSize(whole_width - arrow_width, whole_height);
  m_text_box->setPosition(0, 0);
}

} // namespace wl
