#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <memory>

#include "Container.hpp"
#include "Widget.hpp"

namespace wl {

class Button : public Widget
{
public:
  Button(Container *parent,
	 Vec2 position = Vec2(0, 0),
	 int width = 0,
	 int height = 0
	 );

  virtual ~Button();
  
  virtual void paint() const override;

private:
  std::function<void()> m_on_release;
  std::function<void()> m_on_press;
};

} // namespace wl

#endif // BUTTON_HPP
