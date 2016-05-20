#ifndef UTIL_HPP
#define UTIL_HPP

#include <algorithm>

#include <graphics.hpp>

namespace wl {

template <typename T>
bool vec_contains(const std::vector<T>& vec, T elem)
{
  return std::find(vec.begin(), vec.end(), elem) != vec.end();
}

template <typename T>
void add_to_vec_uniquely(std::vector<T>& vec, T elem)
{
  if (!vec_contains(vec, elem))
    vec.emplace_back(elem);
}

template <typename T>
void remove_from_vec(std::vector<T>& vec, unsigned int index)
{
  auto it =vec.begin() + index;
  if (it < vec.end())
    vec.erase(it);
}

template <typename T>
void remove_from_vec(std::vector<T>& vec, T elem)
{
  auto it = std::find(vec.begin(), vec.end(), elem);
  if (it < vec.end())
    vec.erase(it);
}

} // namespace wl

#endif // UTIL_HPP
