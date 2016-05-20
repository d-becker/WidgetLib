#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "WidgetLib/Selector.hpp"

#include <memory>

namespace wl {

class Checkbox : public Selector
{
public:
  Checkbox(Vec2 position,
	   int width,
	   int height);

  virtual ~Checkbox();

  virtual void paint() override;
};

} // namespace wl

#endif // CHECKBOX_HPP
