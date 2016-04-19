#ifndef SPINNER_HPP
#define SPINNER_HPP

#include "Container.hpp"

#include "TextBox.hpp"
#include "Vec2.hpp"

namespace wl {

class Spinner : public Container
{
public:
  Spinner(Vec2 position = Vec2(0, 0),
	  int width = 50,
	  int height = 50);

  virtual ~Spinner();

  virtual void layOutChildren() override;
  
private:
  class ArrowButton;
  TextBox *m_text_box;
  ArrowButton *m_arrow_up;
  ArrowButton *m_arrow_down;
};

} // namespace wl

#endif // SPINNER_HPP
