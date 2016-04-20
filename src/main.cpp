#include <iostream>

#include <graphics.hpp>

#include "Button.hpp"
#include "Spinner.hpp"
#include "DefaultSpinnerModel.hpp"
#include "NumberSpinnerModel.hpp"
#include "TextBox.hpp"
#include "Widget.hpp"

#include "ButtonEvent.hpp"
#include "ButtonObserver.hpp"
#include "ButtonObserverAdapter.hpp"
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

int main()
{
  Toplevel* tl = new Toplevel(400, 400);
  Button* b = new Button(Vec2(50, 50), 60, 60);
  TextBox *tb = new TextBox(Vec2(110, 50), 80, 40);
  Spinner<int> *sp = new Spinner<int>(std::make_shared<DefaultSpinnerModel>(),
				 Vec2(50, 150), 100, 25);

  std::shared_ptr<ButtonObserver> bo = make_shared<ButtonObserverAdapter>([](const ButtonEvent& evt) {
      static unsigned int counter = 0;
      cerr << "Button clicked: " << counter++ << "!!!\n";
      return true;
    });
  std::shared_ptr<KeyObserver> ko = make_shared<KeyObserverAdapter>([](const KeyEvent& evt){
      static unsigned int counter = 0;
      cerr << "Key event  handled: " << counter++ << "!!!\n";
      return false;
    });
  
  b->addButtonObserver(bo);
  
  //tl->addKeyObserver(ko);
  tl->setBackgroundColour(genv::color(0, 150, 0));

  tl->addChild(b);
  tl->addChild(tb);
  tl->addChild(sp);

  tl->mainloop();
  
  delete tl;

  // Testing text
  string A = "A";
  string V = "V";
  string AV = A + V;

  string a = "a";
  string space = " ";

  cout << "String A: " << gout.twidth(A) << ".\n";
  cout << "String V: " << gout.twidth(V) << ".\n";
  cout << "String AV: " << gout.twidth(AV) << ".\n";
  cout << "String a: " << gout.twidth(a) << ".\n";
  cout << "String space: " << gout.twidth(space) << ".\n";
  return 0;
}
