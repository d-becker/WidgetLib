#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <memory>

#include "Container.hpp"
#include "MouseEvent.hpp"
#include "Widget.hpp"

#include <functional>

namespace wl {

class Button : public Widget
{
public:
  Button(Vec2 position = Vec2(0, 0),
	 int width = 50,
	 int height = 50,
	 std::function<bool(const MouseEvent&)> callback = {}
	 );

  virtual ~Button();
  
  virtual void paint() override;

private:
  std::function<bool(const MouseEvent&)>  m_callback;
};

} // namespace wl

#endif // BUTTON_HPP
