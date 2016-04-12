#include <iostream>

#include <graphics.hpp>

#include "Button.hpp"
#include "Widget.hpp"

#include "Event.hpp"
#include "MouseEvent.hpp"

using namespace std;
using namespace genv;
using namespace wl;

int main()
{
  cout << "Hello World." << endl;
  gout.open(400, 400);

  Button b(nullptr);
  
  event ev;
  while(gin >> ev);
  return 0;
}
