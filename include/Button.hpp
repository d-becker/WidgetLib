#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <memory>

#include "Container.hpp"
#include "Widget.hpp"

namespace wl {

class Button : public Widget
{
public:
  Button(Container *parent,
	 Vec2 position = Vec2(0, 0),
	 int width = 0,
	 int height = 0,
	 std::function<void()> on_release = {},
	 std::function<void()> on_press = {}
	 );

  virtual ~Button();

  /**
   * Sets the function that is executed upon releasing the left mouse button to
   * \a on_release.
   *
   * \param on_release The function that will be executed upon releasing the left
   *        mouse button to \a on_release.
   */
  void bindOnRelease(std::function<void()> on_release);

  /**
   * Sets the function that is executed upon pressing the left mouse button to
   * \a on_press.
   *
   * \param on_press The function that will be executed upon pressing the left
   *        mouse button to \a on_press.
   */
  void bindOnPress(std::function<void()> on_press);
  
  virtual void handleEvent(const genv::event& evt) override;
  virtual void paint() const override;

private:
  std::function<void()> m_on_release;
  std::function<void()> m_on_press;
};

} // namespace wl

#endif // BUTTON_HPP
