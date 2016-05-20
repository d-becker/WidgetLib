#ifndef SELECTION_GROUP_EVENT_HPP
#define SELECTION_GROUP_EVENT_HPP

#include "WidgetLib/evt/Event.hpp"

#include <string>

namespace wl {

class SelectionGroupEvent : public Event
{
public:
  SelectionGroupEvent(Widget *source,
		      std::string new_selection)
    : Event(source),
      m_new_selection(new_selection)
  {
  }

  virtual ~SelectionGroupEvent() {}

  const std::string& getNewSelection() const
  {
    return m_new_selection;
  }
  
private:
  const std::string m_new_selection;
};

} // namespace wl

#endif // SELECTION_GROUP_EVENT_HPP
