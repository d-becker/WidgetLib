#ifndef CHECKBOX_OBSERVER_ADAPTER_HPP
#define CHECKBOX_OBSERVER_ADAPTER_HPP

#include "CheckboxObserver.hpp"

#include <functional>

namespace wl {

class CheckboxObserverAdapter : public CheckboxObserver
{
public:
  CheckboxObserverAdapter(std::function<bool(const CheckboxEvent&)> callback)
    : m_callback(callback)
  {
  }

  virtual ~CheckboxObserverAdapter() {}

  virtual bool handleCheckboxEvent(const CheckboxEvent& evt) override
  {
    if (m_callback)
      return m_callback(evt);
    else
      return false;
  }

private:
  std::function<bool(const CheckboxEvent&)> m_callback
};

} // namespace wl

#endif // CHECKBOX_OBSERVER_ADAPTER_HPP
