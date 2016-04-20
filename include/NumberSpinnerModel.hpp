#ifndef NUMBER_SPINNER_MODEL_H
#define NUMBER_SPINNER_MODEL_H

#include "SpinnerModel.hpp"

#include <stdexcept>

namespace wl {

template<typename N>
class NumberSpinnerModel: public SpinnerModel<N>
{
public:
  NumberSpinnerModel(N lower_limit,
		     N upper_limit,
		     N step = 1,
		     N value = 0)
    : m_lower_limit(lower_limit),
      m_upper_limit(upper_limit),
      m_step(step),
      m_value(value)
  {
    if (m_lower_limit > m_upper_limit)
      throw std::invalid_argument(
		 "The lower limit cannot be higher than the higher limit.");
    if (m_step < 0)
      throw std::invalid_argument("The step cannot be negative.");
  }

  virtual N getCurrentValue() const override
  {
    return m_value;
  }

  virtual void setCurrentValue(N value) override
  {
    m_value = value;
  }

  virtual void increment() override
  {
    m_value += m_step;
    if (m_value > m_upper_limit)
      m_value = m_upper_limit;
  }

  virtual void decrement() override
  {
    m_value -= m_step;
    if (m_value < m_lower_limit)
      m_value = m_lower_limit;
  }

private:
  N m_value;

  const N m_lower_limit;
  const N m_upper_limit;
  const N m_step;
};

} // namespace wl

#endif // NUMBER_SPINNER_MODEL_H
