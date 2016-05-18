#include "Selection.hpp"

#include "evt/MouseEvent.hpp"
#include "evt/KeyEvent.hpp"
#include "evt/ObserverAdapter.hpp"

namespace wl {

Selection::Selection(Vec2 position,
		     int width,
		     int height,
		     std::string title,
		     const std::vector<std::string>& options,
		     int title_bar_height)
  : Container(position, width, height),
    m_title_bar_height(title_bar_height > 0 ? title_bar_height : 0),
    m_title_bar(new Label(Vec2(0, 0), width, m_title_bar_height, title)),
    m_panel(new SelectablePanel(Vec2(0, m_title_bar_height),
				width, height - m_title_bar_height, options))
{
  // Adding the children
  addChild(m_title_bar);
  addChild(m_panel);

  // Grab focus and on click
  addMouseSuperObserver(std::make_shared< ObserverAdapter<MouseEvent> >(
					 [this](const MouseEvent& evt) {
	if (evt.getEvtType() == MouseEvent::MOUSE_BTN_PRESSED)
	{
	  grabFocus();
	  return true;
	}
	
	return false;
      }));

  // Handle up and down buttons
  addKeySuperObserver(
    std::make_shared< ObserverAdapter<KeyEvent> >(
		     [this](const KeyEvent& evt) {
       bool handled = false;
       if (evt.getEvtType() == KeyEvent::KEY_PRESSED)
       {
	 int keycode = evt.getKeycode();
	 switch (keycode)
	 {
	  case genv::key_up:
	  {
	    m_panel->scrollUp();
	    handled = true;
	    break;
	  }

	  case genv::key_down:
	  {
	    m_panel->scrollDown();
	    handled = true;
	    break;
	  }
         }
       }

     return handled;	    
   }));
}

Selection::~Selection()
{
}

const std::vector<std::string> Selection::getOptions() const
{
  return m_panel->getOptions();
}

bool Selection::addOption(std::string option)
{
  return m_panel->addOption(option);
}

bool Selection::removeOption(const std::string& option)
{
  return m_panel->removeOption(option);
}

const std::string& Selection::getSelected() const
{
  return m_panel->getSelected();
}

bool Selection::setSelected(const std::string& option)
{
  return m_panel->setSelected(option);
}

void Selection::clearSelection()
{
  m_panel->clearSelection();
}

void Selection::layOutChildren()
{
  int width = getWidth();
  int height = getHeight();
  
  if (m_title_bar)
  {
    m_title_bar->setPosition(0, 0);
    m_title_bar->setSize(width, m_title_bar_height);
  }

  if (m_panel)
  {
    m_panel->setPosition(0, m_title_bar_height);
    m_panel->setSize(width, height - m_title_bar_height);
  }
}

} // namespace wl
