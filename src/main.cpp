#include <fstream>

#include <graphics.hpp>

#include "WidgetLib/NumberSpinner.hpp"
#include "WidgetLib/Selection.hpp"
#include "WidgetLib/Toplevel.hpp"

#include "WidgetLib/evt/Event.hpp"
#include "WidgetLib/evt/KeyEvent.hpp"
#include "WidgetLib/evt/MouseEvent.hpp"
#include "WidgetLib/evt/Observer.hpp"
#include "WidgetLib/evt/ObserverAdapter.hpp"

using namespace std;
using namespace genv;
using namespace wl;

void write_to_file(NumberSpinner<int> *ns1,
		   NumberSpinner<int> *ns2,
		   Selection *sel1,
		   Selection *sel2,
		   std::string filename = "log.txt")
{  
  ofstream out(filename);
  out << "First number selector:\t"
      << (ns1 ? to_string(ns1->getCurrentValue()) : "nullptr") << endl
      << "Second number selector:\t"
      << (ns2 ? to_string(ns2->getCurrentValue()) : "nullptr") << endl
      << "First selection widget:\t"
      << (sel1 ? sel1->getSelected() : "nullptr") << endl
      << "Second selection widget:\t"
      << (sel2 ? sel2->getSelected() : "nullptr") << endl;

  // RAII - the destructor closes the file stream
}

int main()
{  
  //
  // Number selector widgets
  //
  // To change the value of the NumberSpinners, you can use the buttons,
  // the up/down/pgup/pgdown keys, but you can also type in the desired
  // value and press enter to validate and push it to the NumberSpinner
  // - if the value is incorrect, the previous value is restored.
  
  // Number range from -10 to 10, step is 2, initial value is 2
  NumberSpinner<int> *nsp1 = new NumberSpinner<int>(Vec2(50, 150), 100, 25,
						  -10, 10, 2, 2);

  // Number range from -15 to 15, step is 1, initial value is 10
  NumberSpinner<int> *nsp2 = new NumberSpinner<int>(Vec2(50, 180), 100, 25,
						  -15, 15, 1, 10);

  //
  // Selection widgets
  //
  // Scroll up and down with the arrows and the mouse wheel
  Selection *sel1 = new Selection(Vec2(50, 225), 100, 90,
		/* Title */   "Fruit",
		/* Options*/ {"Apple", "Pear", "Plum", "Orange", "Grapefruit"});

  Selection *sel2 = new Selection(Vec2(160, 225), 100, 90,
		/* Title */   "Language",
                /* Options*/ {"Norwegian", "Swedish", "Danish", "Icelandic",
			      "Faroese", "Finnish"});

  //
  // Creating the toplevel widget and adding observers
  //
  Toplevel* tl = new Toplevel(400, 400);

  // Escape on pressing the esc button (if no other widget handled the key event)
  tl->addKeyObserver(std::make_shared< ObserverAdapter<KeyEvent> >([tl](const KeyEvent& evt) {
	if (evt.getKeycode() == genv::key_escape)
	{
	  tl->stopMainLoop();
	  return true;
	}
	return false;
      }));

  // Save the values in log.txt on pressing Shift+S
  tl->addKeyObserver(std::make_shared< ObserverAdapter<KeyEvent> >([=](const KeyEvent& evt) {
	if (evt.getKeycode() == 'S')
	{
	  write_to_file(nsp1, nsp2, sel1, sel2);
	  return true;
	}
	return false;
      }));
  
  tl->setBackgroundColour(genv::color(0, 150, 0));

  // Adding the widgets as children of the Toplevel widget
  tl->addChild(nsp1);
  tl->addChild(nsp2);
  tl->addChild(sel1);
  tl->addChild(sel2);

  // Starting the main loop
  tl->mainloop();
  
  delete tl; // Recursively deletes all children

  return 0;
}
