#include <iostream>

#include <graphics.hpp>

#include "Button.hpp"
#include "Widget.hpp"

#include "Event.hpp"
#include "FocusEvent.hpp"
#include "FocusObserver.hpp"
#include "FocusObserverAdapter.hpp"
#include "KeyEvent.hpp"
#include "KeyObserver.hpp"
#include "KeyObserverAdapter.hpp"
#include "MouseEvent.hpp"
#include "MouseObserver.hpp"
#include "MouseObserverAdapter.hpp"
#include "Toplevel.hpp"

using namespace std;
using namespace genv;
using namespace wl;

class ML : public MouseObserver
{
  virtual bool handleMouseEvent(const MouseEvent& evt) override
  {
    static unsigned int counter = 0;
    cerr << "Mouse event handled: " << counter++ << "!!!\n";
    return true;
  }
};

class KL : public KeyObserver
{
  virtual bool handleKeyEvent(const KeyEvent& evt) override
  {
    static unsigned int counter = 0;
    cerr << "Key event  handled: " << counter++ << "!!!\n";
    return true;
  }
};

int main()
{
  Toplevel* tl = new Toplevel(400, 400);
  Button* b = new Button(tl, Vec2(50, 50), 60, 60, [](const MouseEvent& evt) {
      static unsigned int counter = 0;
      cerr << "Button clicked: " << counter++ << "!!!\n";
      return true;
    });

  std::shared_ptr<MouseObserver> mo = make_shared<MouseObserverAdapter>([](const MouseEvent& evt){
      static unsigned int counter = 0;
      cerr << "Mouse event handled: " << counter++ << "!!!\n";
      return true;
    });
  std::shared_ptr<KeyObserver> ko = make_shared<KeyObserverAdapter>([](const KeyEvent& evt){
      static unsigned int counter = 0;
      cerr << "Key event  handled: " << counter++ << "!!!\n";
      return true;
    });
  b->addMouseObserver(mo);
  tl->addKeyObserver(ko);

  tl->mainloop();
  
  delete tl;
  return 0;
}
