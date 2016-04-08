#include <iostream>

#include <graphics.hpp>

#include "Button.hpp"
#include "Widget.hpp"

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
