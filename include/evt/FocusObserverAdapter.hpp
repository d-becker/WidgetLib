#ifndef FOCUS_OBSERVER_ADAPTER_HPP
#define FOCUS_OBSERVER_ADAPTER_HPP

#include "FocusObserver.hpp"

#include <functional>

namespace wl {

class FocusObserverAdapter : public FocusObserver
{
public:
  FocusObserverAdapter(std::function<bool(const FocusEvent&)> callback)
    : m_callback(callback)
  {
  }

  virtual ~FocusObserverAdapter() {}

  virtual bool handleFocusEvent(const FocusEvent& evt) override
  {
    if (m_callback)
      return m_callback(evt);
    else
      return false;			  
  }
  
private:
  std::function<bool(const FocusEvent&)> m_callback;
};

} // namespace wl

#endif // FOCUS_OBSERVER_ADAPTER_HPP
