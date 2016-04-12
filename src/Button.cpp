#include "Button.hpp"

namespace wl {

Button::Button(Container *parent,
	       Vec2 position,
	       int width,
	       int height,
	       std::function<void()> on_release,
	       std::function<void()> on_press
	       )
  : Widget(parent, position, width, height),
    m_on_release(on_release),
    m_on_press(on_press)
{
}

Button::~Button()
{
}

void Button::bindOnRelease(std::function<void()> on_release)
{
  m_on_release = on_release;
}

void Button::bindOnPress(std::function<void()> on_press)
{
  m_on_press = on_press;
}

void Button::paint() const
{
}

} // namespace wl
