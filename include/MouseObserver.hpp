#ifndef MOUSE_OBSERVER_HPP
#define MOUSE_OBSERVER_HPP

#include "MouseEvent.hpp"

namespace wl {

class MouseObserver
{
public:
  virtual bool handleMouseEvent(const MouseEvent& evt) = 0;
};

} // namespace wl

#endif // MOUSE_OBSERVER_HPP
