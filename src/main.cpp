#include <iostream>

#include <graphics.hpp>

#include "Button.hpp"
#include "Checkbox.hpp"
#include "NumberSpinner.hpp"
#include "Spinner.hpp"
#include "DefaultSpinnerModel.hpp"
#include "Label.hpp"
#include "NumberSpinnerModel.hpp"
#include "RadioButton.hpp"
#include "Selectable.hpp"
#include "SelectablePanel.hpp"
#include "SelectionGroup.hpp"
#include "TextBox.hpp"
#include "Widget.hpp"

#include "ButtonEvent.hpp"
#include "Event.hpp"
#include "FocusEvent.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"
#include "Observer.hpp"
#include "ObserverAdapter.hpp"
#include "Toplevel.hpp"

using namespace std;
using namespace genv;
using namespace wl;

int main()
{
  Toplevel* tl = new Toplevel(400, 400);
  Button* b = new Button(Vec2(50, 50), 60, 60);
  TextBox *tb = new TextBox(Vec2(110, 50), 80, 40);
  NumberSpinner<int> *sp = new NumberSpinner<int>(Vec2(50, 150), 100, 25,
						  -10, 10, 2, 2);
  Label *l = new Label(Vec2(50, 180), 100, 25, "Label");
  Checkbox *cb = new Checkbox(Vec2(50, 220), 25, 25);
  //Selectable *sel1 = new Selectable(Vec2(50, 250), 75, 25);
  //Selectable *sel2 = new Selectable(Vec2(50, 250), 75, 25);
  SelectablePanel *spanel = new SelectablePanel(Vec2(50, 250), 100, 90, {"Alma", "Körte", "Szilva", "Narancs", "Grépfrút"});
  //SelectionGroup *sg = new SelectionGroup(Vec2(50, 250), 100, 90, {"Alma", "Körte", "Szilva"});

  std::shared_ptr< Observer<ButtonEvent> > bo = make_shared< ObserverAdapter<ButtonEvent> >([](const ButtonEvent& evt) {
      static unsigned int counter = 0;
      cerr << "Button clicked: " << counter++ << "!!!\n";
      return true;
    });
  std::shared_ptr< Observer<KeyEvent> > ko = make_shared< ObserverAdapter<KeyEvent> >([](const KeyEvent& evt){
      static unsigned int counter = 0;
      cerr << "Key event  handled: " << counter++ << "!!!\n";
      return false;
    });
  std::shared_ptr< Observer<MouseEvent> > mo = make_shared< ObserverAdapter<MouseEvent> >([](const MouseEvent& evt) {
      static unsigned int counter = 0;
      cerr << "Mouse event: " << counter++ << "!!!\n";
      return true;
    });
  
  b->addObserver(bo);
  //cb->addMouseObserver(mo);
					    
  //tl->addKeyObserver(ko);
  tl->setBackgroundColour(genv::color(0, 150, 0));

  tl->addChild(b);
  tl->addChild(tb);
  tl->addChild(sp);
  tl->addChild(l);
  tl->addChild(cb);
  tl->addChild(spanel);
  //tl->addChild(sg);

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
