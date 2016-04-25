#ifndef SELECTOR_OBSERVER_ADAPTER_HPP
#define SELECTOR_OBSERVER_ADAPTER_HPP

#include "SelectorObserver.hpp"

#include <functional>

namespace wl {

class SelectorObserverAdapter : public SelectorObserver
{
public:
  SelectorObserverAdapter(std::function<bool(const SelectorEvent&)> callback)
    : m_callback(callback)
  {
  }

  virtual ~SelectorObserverAdapter() {}

  virtual bool handleSelectorEvent(const SelectorEvent& evt) override
  {
    if (m_callback)
      return m_callback(evt);
    else
      return false;
  }

private:
  std::function<bool(const SelectorEvent&)> m_callback;
};

} // namespace wl

#endif // SELECTOR_OBSERVER_ADAPTER_HPP
