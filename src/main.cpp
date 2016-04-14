#include <iostream>

#include <graphics.hpp>

#include "Button.hpp"
#include "Widget.hpp"

#include "Event.hpp"
#include "MouseEvent.hpp"
#include "MouseObserver.hpp"
#include "Toplevel.hpp"

using namespace std;
using namespace genv;
using namespace wl;

class ML : public MouseObserver
{
  virtual bool handleMouseEvent(const MouseEvent& evt) override
  {
    static unsigned int counter = 0;
    cerr << "Event handled :" << counter++ << "!!!\n";
    return true;
  }
};

int main()
{
  Toplevel* tl = new Toplevel(400, 400);
  Button* b = new Button(tl, Vec2(50, 50), 60, 60);

  std::shared_ptr<MouseObserver> mo = make_shared<ML>();
  b->addMouseObserver(mo);

  tl->mainloop();
  
  delete tl;
  return 0;
}
