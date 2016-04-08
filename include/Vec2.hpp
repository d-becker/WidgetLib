#ifndef VEC2_HPP
#define VEC2_HPP

namespace wl {

class Vec2
{
public:
  Vec2(int p_x,
       int p_y)
    : x(p_x),
      y(p_y)
  {
  }

  Vec2()
    : Vec2(0, 0)
  {
  }

  Vec2& operator=(const Vec2& other)
  {
    x = other.x;
    y = other.y;
    return *this;
  }

  Vec2& operator+=(const Vec2& other)
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2& operator-=(const Vec2& other)
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vec2& operator*=(int scalar)
  {
    x *= scalar;
    y *= scalar;
    return *this;
  }


  int x;
  int y;
};

inline Vec2 operator+(Vec2 lhs,
		      const Vec2& rhs)
{
  return lhs+=rhs;
}

inline Vec2 operator-(Vec2 lhs,
		      const Vec2& rhs)
{
  return lhs-=rhs;
}

inline Vec2 operator*(Vec2 lhs,
		      int scalar)
{
  return lhs*=scalar;
}

inline bool operator==(const Vec2& lhs,
		       const Vec2& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

} // namespace wl.

#endif //  VEC2_HPP
