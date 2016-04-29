#include "Selection.hpp"

namespace wl {

Selection::Selection(Vec2 position,
		     int width,
		     int height,
		     const std::vector<std::string>& options,
		     std::string title,
		     int title_bar_height)
  : Container(position, width, height),
    m_title_bar_height(title_bar_height > 0 ? title_bar_height : 0),
    m_title_bar(new Label(Vec2(0, 0), width, m_title_bar_height, title)),
    m_panel(new SelectablePanel(Vec2(0, m_title_bar_height),
				width, height, options))
{
  // Adding the children
  addChild(m_title_bar);
  addChild(m_panel);
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
