#include "Toplevel.hpp"

namespace wl {

Toplevel::Toplevel(std::shared_ptr<Container> parent,
		   Vec2 position = Vec2(0, 0),
		   int width = 0,
		   int height = 0)
  : Container(parent, position, width, height),
    m_mouse_btn_left_pressed(nullptr),
    m_mouse_btn_right_pressed(nullptr),
    m_mouse_inside(nullptr)
{
}

Toplevel::~Toplevel()
{
}

} // namespace wl
