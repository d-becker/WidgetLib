#ifndef LABEL_HPP
#define LABEL_HPP

#include "TextDisplay.hpp"

#include <string>

namespace wl {

class Label : public TextDisplay
{
public:
  Label(Vec2 position = Vec2(0, 0),
	int width = 50,
	int height = 50,
	std::string text = "Label");

  virtual ~Label();

  /**
   * Returns the text of the label.
   *
   * \return The text of the label.
   */
  std::string getText() const;

  /**
   * Sets the text of the label.
   *
   * \param text The new text of the label.
   */
  void setText(std::string text);

protected:
  virtual std::string get_text_to_display() const override;
private:
};

} // namespace wl

#endif // LABEL_HPP
