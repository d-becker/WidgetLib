#ifndef OBSERVER_ADAPTER_HPP
#define OBSERVER_ADAPTER_HPP

#include "Observer.hpp"

namespace wl {

template <typename EV>
class ObserverAdapter : public Observer<EV>
{
public:
  ObserverAdapter(std::function<bool(const EV&)> callback)
    : m_callback(callback)
  {
  }

  virtual bool handleEvent(const EV& evt) override
  {
    if (m_callback)
      return m_callback(evt);
    else
      return false;
  }

private:
  std::function<bool(const EV&)> m_callback
};

} // namespace

#endif // OBSERVER_ADAPTER_HPP
