#include "Toplevel.hpp"

namespace wl {

Toplevel::Toplevel(Vec2 position,
		   int width,
		   int height)
  : Container(nullptr, position, width, height),
    m_mouse_btn_left_pressed(nullptr),
    m_mouse_btn_right_pressed(nullptr),
    m_mouse_inside(nullptr)
{
}

Toplevel::~Toplevel()
{
}

} // namespace wl
