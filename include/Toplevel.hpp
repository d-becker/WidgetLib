#ifndef TOPLEVEL_H
#define TOPLEVEL_H

#include "Container.hpp"

namespace wl {

class Toplevel : public Container
{
public:
  Toplevel(Vec2 position = Vec2(0, 0),
	   int width = 0,
	   int height = 0);

  virtual ~Toplevel();

private:
  Widget *m_mouse_btn_left_pressed;
  Widget *m_mouse_btn_right_pressed;
  Widget *m_mouse_inside;
};

} // namespace wl

#endif // TOPLEVEL_H
