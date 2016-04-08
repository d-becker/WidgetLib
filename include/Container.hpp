#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>

#include "Widget.hpp"

namespace wl {

class Container : public Widget
{
public:
  Container(std::shared_ptr<Container> parent,
	    Vec2 position = Vec2(0, 0),
	    int width = 0,
	    int height = 0);
  
  virtual ~Container();

  const std::vector<Widget>& getChildren() const;
  
private:
  std::vector<Widget> m_children;
};

} // namespace wl

#endif // CONTAINER_HPP
