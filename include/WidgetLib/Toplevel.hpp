#ifndef TOPLEVEL_H
#define TOPLEVEL_H

#include "WidgetLib/FreePanel.hpp"

namespace wl {

class Toplevel : public FreePanel
{
public:
  Toplevel(int width,
	   int height,
	   unsigned int refresh_rate = 60);

  virtual ~Toplevel();

  virtual Toplevel *getToplevel() override;
  
  void mainloop();
  void stopMainLoop();

  /**
   * Returns a pointer to the widget that currently has focus.
   *
   * \return A pointer to the widget that currently has focus (or \c nullptr if
   *         no widget has focus).
   */
  Widget *getFocussed() const;

  /**
   * Sets the focus to the provided widget.
   *
   * \param focussed The widget to give the focus to.
   */
  void setFocussed(Widget *focussed);
  
private:
  void handle_genv_event(const genv::event& g_evt);
  
  void handle_genv_mouse_event(const genv::event& g_evt);
  void handle_genv_mouse_event_no_button(const genv::event& g_evt);
  void handle_genv_mouse_event_button(const genv::event& g_evt);
  void handle_genv_mouse_event_wheel(const genv::event& g_evt);
  void handle_genv_mouse_event_normal_button(const genv::event& g_evt);
  
  void handle_genv_key_event(const genv::event& g_evt);
  
private:
  Widget *m_mouse_btn_left_pressed;
  //Widget *m_mouse_btn_right_pressed;
  Widget *m_mouse_inside;

  Widget *m_focussed;

  unsigned int m_refresh_rate;

  bool m_looping;
};

} // namespace wl

#endif // TOPLEVEL_H
