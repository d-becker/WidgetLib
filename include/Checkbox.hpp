#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "Selector.hpp"

#include <memory>

namespace wl {

class Checkbox : public Selector
{
public:
  Checkbox(Vec2 position = Vec2(0, 0),
	   int width = 50,
	   int height = 50);

  virtual ~Checkbox();

  virtual void paint() override;
};

} // namespace wl

#endif // CHECKBOX_HPP
