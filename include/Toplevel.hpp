#ifndef TOPLEVEL_H
#define TOPLEVEL_H

#include <memory>
#include "Container.hpp"

namespace wl {

class Toplevel : public Container
{
public:
  Toplevel(std::shared_ptr<Container> parent,
	   Vec2 position = Vec2(0, 0),
	   int width = 0,
	   int height = 0);

  virtual ~Toplevel();

private:
  std::shared_ptr<Widget> m_mouse_btn_left_pressed;
  std::shared_ptr<Widget> m_mouse_btn_right_pressed;
  std::shared_ptr<Widget> m_mouse_inside;
};

} // namespace wl

#endif // TOPLEVEL_H
