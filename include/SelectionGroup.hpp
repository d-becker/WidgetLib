#ifndef SELECTION_GROUP_HPP
#define SELECTION_GROUP_HPP

#include "Container.hpp"

#include <string>
#include <vector>

#include "SelectablePanel.hpp"

namespace wl {

class SelectionGroup : public Container
{
public:
  SelectionGroup(Vec2 position = Vec2(0, 0),
		 int width = 50,
		 int height = 50,
		 std::vector<std::string> options);

  virtual ~SelectionGroup();

  /**
   * Adds a new option to this \c SelectionGroup object if that option is not
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
  bool removeOption(std::string option);

  /**
   * Returns the option that is currently selected.
   * If no option is selected, returns an empty string.
   *
   * \return The option that is currently selected.
   */
  std::string getSelected() const;

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

  virtual void paint() override;
private:
  SelectablePanel *m_panel;
};

} // namespace wl

#endif // SELECTION_GROUP_HPP
