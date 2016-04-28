#ifndef RESIZE_OBSERVER_ADAPTER_HPP
#define RESIZE_EVENT_HPP

#include "ResizeObserver.hpp"

#include <functional>

namespace wl {

class ResizeObserverAdapter : public ResizeObserver
{
public:
  ResizeObserverAdapter(std::function<bool(const ResizeEvent&)> callback)
    : m_callback(callback)
  {
  }

  virtual ~ResizeObserverAdapter() {}

  virtual bool handleResizeEvent(const ResizeEvent& evt) override
  {
    if (m_callback)
      return m_callback(evt);
    else
      return false;
  }
  
private:
  std::function<bool(const ResizeEvent&)> m_callback;
};

} // namespace wl

#endif // RESIZE_OBSERVER_ADAPTER_HPP
