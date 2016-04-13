#include <iostream>

#include <graphics.hpp>
/*
#include "Button.hpp"
#include "Widget.hpp"

#include "Event.hpp"
#include "MouseEvent.hpp"*/

using namespace std;
using namespace genv;
//using namespace wl;

int main()
{
  cout << "Hello World." << endl;
  gout.open(400, 400);

  canvas c;
  c.open(50, 50);
  c << move_to(0, 0);
  c << color(0, 0, 255);
  c<< box(50, 50);

  c << refresh;

  gout << stamp(c, 375, 100);

  unsigned int counter = 0;

  gout << refresh;
  
  event ev;
  while(gin >> ev)
  {
    cerr << "Loop " << counter++ << ".\n";
    if (ev.keycode == key_escape)
      break;
  }
  
  return 0;
}
