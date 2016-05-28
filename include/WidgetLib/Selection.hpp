#ifndef SELECTION_HPP
#define SELECTION_HPP

#include "WidgetLib/Container.hpp"
#include "WidgetLib/EventEmitter.hpp"
#include "WidgetLib/evt/SelectionGroupEvent.hpp"
#include "WidgetLib/Label.hpp"
#include "WidgetLib/SelectablePanel.hpp"

namespace wl {

class Selection : public Container,
		  public EventEmitter<SelectionGroupEvent>
{
public:
  Selection(Vec2 position,
	    int width,
	    int height,
	    std::string title = "Selection",
	    const std::vector<std::string>& options = {},
	    int title_bar_height = 25);
  virtual ~Selection();

  /**
   * Returns a vector of the options that are contained in
   * this \c Selection.
   *
   * \return A vector of the options that are contained in
   *         this \c Selection.
   */
  const std::vector<std::string> getOptions() const;

  /**
   * Adds a new option to this \c Selection object if that option is not
   * already added.
   *
   * \param option The option to add.
   *
   * \return \c true if the option was added; \c false otherwise.
   */
  bool addOption(std::string option);

  /**
   * Removes an option from this \c Selection object if that option is
   * contained in it.
   *
   * \param option The option to remove.
   *
   * \return \c true if the option was removed; \c false otherwise.
   */
  bool removeOption(const std::string& option);

  /**
   * Returns the option that is currently selected.
   * If no option is selected, returns an empty string.
   *
   * \return The option that is currently selected.
   */
  const std::string& getSelected() const;

  /**
   * Sets the selection to the given option if that option is contained in
   * this \c Selection object and deselects all other options.
   *
   * \param option The option to select.
   *
   * \return \c true if the selection was set to the given option;
   *         \c false otherwise.
   */
  bool setSelected(const std::string& option);

  /**
   * Deselects all options.
   */
  void clearSelection();

  virtual void layOutChildren() override;
  
private:
  int m_title_bar_height;

  Label *m_title_bar;
  SelectablePanel *m_panel;
};

} // namespace wl

#endif // SELECTION_HPP
