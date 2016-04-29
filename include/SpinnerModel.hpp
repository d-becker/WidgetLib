#ifndef SPINNER_MODEL_HPP
#define SPINNER_MODEL_HPP

namespace wl {

template <typename T>
class SpinnerModel
{
public:
  virtual ~SpinnerModel() {}
  
  /**
   * Returns the current value.
   *
   * \return The current value.
   */
  virtual T getCurrentValue() const = 0;

  /**
   * Sets the current value.
   * Implementations are allowed to do nothing in this method.
   *
   * \param value The new value.
   *
   * \return \c true if the value was set; \c false otherwise.
   */
  virtual bool setCurrentValue(T value) = 0;

  /**
   * Increments the current value.
   */
  virtual void increment() = 0;

  /**
   * Decrements the current value.
   */
  virtual void decrement() = 0;
};

} // namespace wl

#endif // SPINNER_MODEL_HPP
