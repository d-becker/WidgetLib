#ifndef NUMBER_SPINNER_HPP
#define NUMBER_SPINNER_HPP

#include <memory>

#include "WidgetLib/NumberSpinnerModel.hpp"
#include "WidgetLib/Spinner.hpp"

namespace wl {

template <typename N>
class NumberSpinner : public Spinner<N>
{
public:
  NumberSpinner(Vec2 position,
	        int width,
	        int height,
		N lower_limit,
		N upper_limit,
		N step = 1,
		N value = 0)
    : Spinner<N>(std::make_shared< NumberSpinnerModel<N> >(lower_limit,
							   upper_limit,
							   step, value),
	      position,
	      width,
	      height)
  {
  }
};

} // namespace wl

#endif // NUMBER_SPINNER_HPP
