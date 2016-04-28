#ifndef SELECTION_OBSERVER_ADAPTER_HPP
#define SELECTION_OBSERVER_ADAPTER_HPP

#include "SelectionObserver.hpp"

#include <functional>

namespace wl {

class SelectionObserverAdapter : public SelectionObserver
{
public:
  SelectionObserverAdapter(std::function<bool(const SelectionEvent&)> callback)
    : m_callback(callback)
  {
  }

  virtual ~SelectionObserverAdapter() {}

  virtual bool handleSelectionEvent(const SelectionEvent& evt) override
  {
    if (m_callback)
      return m_callback(evt);
    else
      return false;
  }

private:
  std::function<bool(const SelectionEvent&)> m_callback;
};

} // namespace wl

#endif // SELECTION_OBSERVER_ADAPTER_HPP
