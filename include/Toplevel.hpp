#ifndef TOPLEVEL_H
#define TOPLEVEL_H

#include "Container.hpp"

namespace wl {

class Toplevel : public Container
{
public:
  Toplevel(int width = 0,
	   int height = 0);

  virtual ~Toplevel();

  virtual Toplevel *getToplevel() override;
  
  void mainloop();
  
private:
  void handle_genv_event(const genv::event& g_evt);
  
  void handle_genv_mouse_event(const genv::event& g_evt);
  void handle_genv_mouse_event_no_button(const genv::event& g_evt);
  void handle_genv_mouse_event_button(const genv::event& g_evt);
  
  void handle_genv_key_event(const genv::event& g_evt);
  
private:
  //Widget *m_mouse_btn_left_pressed;
  //Widget *m_mouse_btn_right_pressed;
  Widget *m_mouse_inside;
};

} // namespace wl

#endif // TOPLEVEL_H
