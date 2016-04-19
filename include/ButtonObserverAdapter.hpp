#ifndef BUTTON_OBSERVER_ADAPTER_HPP
#define BUTTON_OBSERVER_ADAPTER_HPP

#include "ButtonObserver.hpp"

#include <functional>

namespace wl {

class ButtonObserverAdapter : public ButtonObserver
{
public:
  ButtonObserverAdapter(std::function<bool(const ButtonEvent&)> callback)
    : m_callback(callback)
  {
  }

  virtual ~ButtonObserverAdapter() {}

  virtual bool handleButtonEvent(const ButtonEvent& evt) override
  {
    if (m_callback)
      return m_callback(evt);
    else
      return false;
  }
  
private:
  std::function<bool(const ButtonEvent&)> m_callback;
};

} // namespace wl

#endif // BUTTON_OBSERVER_ADAPTER_HPP
