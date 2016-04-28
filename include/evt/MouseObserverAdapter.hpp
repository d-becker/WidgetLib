#ifndef MOUSE_OBSERVER_ADAPTER_HPP
#define MOUSE_OBSERVER_ADAPTER_HPP

#include "MouseObserver.hpp"

#include <functional>

namespace wl {

class MouseObserverAdapter : public MouseObserver
{
public:
  MouseObserverAdapter(std::function<bool(const MouseEvent&)> callback)
    : m_callback(callback)
  {
  }

  virtual ~MouseObserverAdapter() {}

  virtual bool handleMouseEvent(const MouseEvent& evt) override
  {
    if (m_callback)
      return m_callback(evt);
    else
      return false;
  }
  
private:
  std::function<bool(const MouseEvent&)> m_callback;
};

} // namespace wl

#endif // MOUSE_OBSERVER_ADAPTER_HPP
