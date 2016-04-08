#ifndef BOX_HPP
#define BOX_HPP

#include "Vec2.hpp"

namespace wl {

class Box
{
public:
  Box(Vec2 upper_left, Vec2 lower_right)
    : m_upper_left(upper_left),
      m_lower_right(lower_right)
  {
  }

  virtual ~Box()
  {
  }

  Vec2 getUpperLeft() const
  {
    return m_upper_left;
  }
  
  Vec2 getUpperRight() const
  {
    return Vec2(m_lower_right.x, m_upper_left.y);
  }
  
  Vec2 getLowerLeft() const
  {
    return Vec2(m_upper_left.x, m_lower_right.y);
  }
  
  Vec2 getLowerRight() const
  {
    return m_lower_right;
  }

  bool intersects(const Box& other) const
  {
    return m_upper_left.x <= other.m_lower_right.x
      && m_lower_right.x >= other.m_upper_left.x
      && m_upper_left.y <= other.m_lower_right.y
      && m_lower_right.y >= other.m_upper_left.y;
  }

  bool isInside(const Vec2& point) const
  {
    return m_upper_left.x <= point.x && point.x <= m_lower_right.x
      && m_upper_left.y <= point.y && point.y <= m_lower_right.y;
  }
  
private:
  const Vec2 m_upper_left;
  const Vec2 m_lower_right;
};

} // namespace wl

#endif // BOX_HPP
