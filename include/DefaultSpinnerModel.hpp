#ifndef DEFAULT_SPINNER_MODEL_HPP
#define DEFAULT_SPINNER_MODEL_HPP

#include "SpinnerModel.hpp"

namespace wl {

class DefaultSpinnerModel : public SpinnerModel<int>
{
public:
  DefaultSpinnerModel(int value = 0)
    : m_value(value)
  {
  }

  virtual ~DefaultSpinnerModel() {}
  
  virtual int getCurrentValue() const override
  {
    return m_value;
  }

  virtual void setCurrentValue(int value) override
  {
    m_value = value;
  }

  virtual void increment() override
  {
    ++m_value;
  }

  virtual void decrement() override
  {
    --m_value;
  }

private:
  int m_value;
};

} // namespace wl

#endif // DEFAULT_SPINNER_MODEL_HPP
