#ifndef KEY_OBSERVER_ADAPTER_HPP
#define KEY_OBSERVER_ADAPTER_HPP

#include "KeyObserver.hpp"

#include <functional>

namespace wl {

class KeyObserverAdapter : public KeyObserver
{
public:
  KeyObserverAdapter(std::function<bool(const KeyEvent&)> callback)
    : m_callback(callback)
  {
  }

  virtual ~KeyObserverAdapter() {}

  virtual bool handleKeyEvent(const KeyEvent& evt) override
  {
    if (m_callback)
      return m_callback(evt);
    else
      return false;
  }
  
private:
  std::function<bool(const KeyEvent&)> m_callback;
};

} // namespace wl

#endif // KEY_OBSERVER_ADAPTER_HPP
