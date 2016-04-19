#include "Spinner.hpp"

#include "Button.hpp"
#include "Container.hpp"
#include "TextBox.hpp"

namespace wl {

namespace {

class ArrowButton : public Button
{
public:
  enum DIRECTION
  {
    UP,
    DOWN
  };
  
  ArrowButton(Vec2 position = Vec2(0, 0),
	      int width = 50,
	      int height = 50,
	      std::function<bool(const MouseEvent&)> callback = {},
	      DIRECTION dir = UP
	      )
    : Button(position, width, height, callback),
      m_dir(dir)
  {
  }

  virtual ~ArrowButton() {}

  virtual void paint() override
  {
    
  }

  
private:
  DIRECTION m_dir;
};

} // anonymous namespace

class Spinner::SpinnerImpl : public Container
{
public:
  SpinnerImpl()
    : Container(Vec2(0, 0), 0, 0) // Size will be set later
  {
    addChild(new TextBox()); // TODO
  }
  
};

} // namespace wl
