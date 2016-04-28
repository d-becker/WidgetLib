#ifndef SELECTABLE_PANEL_HPP
#define SELECTABLE_PANEL_HPP

#include <string>
#include <vector>

#include "Container.hpp"
#include "EventEmitter.hpp"
#include "Selectable.hpp"
#include "SelectionGroupEvent.hpp"

namespace wl {

/**
 * A panel that contains \c Selectable objects and displays them vertically.
 */
class SelectablePanel : public Container,
			public EventEmitter<SelectionGroupEvent>
{
public:
  SelectablePanel(Vec2 position = Vec2(0, 0),
		  int width = 50,
		  int height = 50,
		  const std::vector<std::string>& options = {});
  virtual ~SelectablePanel();

  /**
   * Returns a vector of the options that are contained in
   * this \c SelectionGroup.
   *
   * \return A vector of the options that are contained in
   *         this \c SelectionGroup.
   */
  const std::vector<std::string> getOptions() const;

  /**
   * Adds a new option to this \c SelectionPanel object if that option is not
   * already added.
   *
   * \param option The option to add.
   *
   * \return \c true if the option was added; \c false otherwise.
   */
  bool addOption(std::string option);

  /**
   * Removes an option from this \c SelectionGroup object if that option is
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
   * this \c SelectionGroup object and deselects all other options.
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

  void scrollUp();
  void scrollDown();

  virtual Widget* getWidgetAtPos(const Vec2& pos) override;
  
  virtual void layOutChildren() override;
  virtual void paint() override;

private:
  Selectable *find_selectable_with_text(const std::string& text);
  bool select_selectable(Selectable *to_select);
  
  std::vector<Selectable*> m_elems;
  Selectable *m_selected;
  unsigned int m_first_to_display; // The index of the first child to display
  int m_elem_height;
};

} // namespace wl

#endif // SELECTABLE_PANEL_HPP
