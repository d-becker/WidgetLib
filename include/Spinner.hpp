#ifndef SPINNER_HPP
#define SPINNER_HPP

#include <memory>
#include <sstream>

#include "Container.hpp"

#include "Button.hpp"
#include "ButtonEvent.hpp"
#include "ButtonObserver.hpp"
#include "ButtonObserverAdapter.hpp"
#include "KeyEvent.hpp"
#include "KeyObserver.hpp"
#include "KeyObserverAdapter.hpp"
#include "MouseEvent.hpp"
#include "MouseObserver.hpp"
#include "MouseObserverAdapter.hpp"
#include "SpinnerModel.hpp"
#include "TextBox.hpp"
#include "Vec2.hpp"

namespace wl {

// Helper functions
template <typename T>
std::string obj_to_str(T o)
{
  std::stringstream s;
  s << o;
  return s.str();
}

template <typename T>
T str_to_obj(const std::string& str)
{
  std::stringstream s(str);
  T res;
  s >> res;
  return res;
}

// Class
template <typename T>
class Spinner : public Container
{
public:
  Spinner(std::shared_ptr< SpinnerModel<T> > model,
	  Vec2 position = Vec2(0, 0),
	  int width = 50,
	  int height = 50)
    : Container(position, width, height),
      m_text_box(new TextBox()),
      m_arrow_up(new ArrowButton(Vec2(0, 0), 0, 0, ArrowButton::UP)),
      m_arrow_down(new ArrowButton(Vec2(0, 0), 0, 0, ArrowButton::DOWN)),
      m_model(model)
  {
    if (!model)
      throw std::invalid_argument("The model must not be a null pointer.");
  
    addChild(m_text_box);
    addChild(m_arrow_up);
    addChild(m_arrow_down);

    update_text_box();

    layOutChildren();

    // Observers
    m_arrow_up->addButtonObserver(
        std::make_shared<ButtonObserverAdapter>([this](const ButtonEvent& evt) {
	    increment();
	    return true;
	}));

    m_arrow_down->addButtonObserver(
        std::make_shared<ButtonObserverAdapter>([this](const ButtonEvent& evt) {
	    decrement();
	    return true;
	}));

    addKeySuperObserver(
       std::make_shared<KeyObserverAdapter>([this](const KeyEvent& evt) {
	  bool handled = false;
	  if (evt.getEvtType() == KeyEvent::KEY_PRESSED)
	  {
	    int keycode = evt.getKeycode();
	    switch (keycode)
	    {
	      case genv::key_enter:
	      {
		// Trying to push the text written by the user
		bool pushed = push_value_in_text_box();

		// If it is not correct, display the correct current value
		if (!pushed)
		  update_text_box();

		handled = true;
		break;
	      }

	      case genv::key_up:
	      {
		increment();
		handled = true;
		break;
	      }

	      case genv::key_down:
	      {
		decrement();
		handled = true;
		break;
	      }

	      case genv::key_pgup:
	      {
		for (int i = 0; i < 10; ++i)
		  increment();
		handled = true;
		break;
	      }

	    case genv::key_pgdn:
	      {
		for (int i = 0; i < 10; ++i)
		  decrement();
		handled = true;
		break;
	      }
	    }
	  }

	  return handled;	    
	}));
  }

  virtual ~Spinner() {}

  /**
   * Returns the model associtated with this \c Spinner.
   *
   * \return The model associtated with this \c Spinner.
   */
  std::shared_ptr< const SpinnerModel<T> > getModel() const
  {
    return m_model;
  }

  /**
   * Sets the model associated with this \c Spinner.
   *
   * \param model The new model. A \c nullptr as this parameter
   *        throws an exception.
   */
  void setModel(std::shared_ptr< SpinnerModel<T> > model)
  {
    if (!model)
      throw std::invalid_argument("The model must not be a null pointer.");
    else
      m_model = model;
  }

  /**
   * Gets the current value of the spinner.
   *
   * \return The current value of the spinner.
   */
  T getCurrentValue() const
  {
    return m_model->getCurrentValue();
  }

  /**
   * Sets the current value of the spinner if the model allows it.
   */
  void setCurrentValue(T value) const
  {
     m_model->setCurrentValue(value);
  }

  /**
   * Increments the current value of the spinner.
   */
  void increment()
  {
    m_model->increment();
    update_text_box();
  }

  /**
   * Decrements the current value of the spinner.
   */
  void decrement()
  {
    m_model->decrement();
    update_text_box();
  }

  virtual void layOutChildren() override
  {
    int whole_width = getWidth();
    int whole_height = getHeight();
    
    int arrow_width = whole_height;
    int arrow_height = whole_height / 2;

    m_arrow_up->setSize(arrow_width, arrow_height);
    m_arrow_down->setSize(arrow_width, arrow_height);

    m_arrow_up->setPosition(whole_width - arrow_width, 0);
    m_arrow_down->setPosition(whole_width - arrow_width, arrow_height);

    m_text_box->setSize(whole_width - arrow_width, whole_height);
    m_text_box->setPosition(0, 0);
  }
  
private:
  bool push_value_in_text_box()
  {
    std::stringstream s(m_text_box->getText());
    T value;
    s >> value;
    bool success = !s.fail();
    if (success)
      m_model->setCurrentValue(value);

    return success;
  }
  
  void update_text_box()
  {
    std::string text = obj_to_str(getCurrentValue());
    m_text_box->setText(text);
  }
  
  class ArrowButton : public Button
  {
  public:
    enum DIRECTION
      {
	UP,
	DOWN
      };
  
    ArrowButton(Vec2 position = Vec2(0, 0),
		int width = 50,
		int height = 50,
		DIRECTION dir = UP)
      : Button(position, width, height),
	m_dir(dir),
	m_arrow_colour(0, 0, 0)
    {
      setBackgroundColour(192,192,192);

      // Grab focus if clicked
      addMouseSuperObserver(std::make_shared<MouseObserverAdapter>([this](const MouseEvent& evt) {
	    if (evt.getEvtType() == MouseEvent::CLICKED_ON_WIDGET)
	      grabFocus();
	    return false;
	  }));
    }

    virtual ~ArrowButton() {}

    virtual void paint() override
    {
      using namespace genv;
      double width = getWidth();
      double height = getHeight();
      std::shared_ptr<canvas> c_ptr = getCanvas();
      if (!c_ptr)
	return;

      canvas& c = *c_ptr;

      // Clearing the canvas
      c << getBackgroundColour()
	<< move_to(0, 0)
	<< box(width, height);

      double x_relative_padding = 0.2; // ratio
      double y_relative_padding = 0.2; // ratio
    
      double x_start = width * x_relative_padding;
      double y_start = m_dir == UP ? height * (1 - y_relative_padding)
	: height * y_relative_padding;

      double y_coeff = m_dir == UP ? -1.0 : 1.0;

      // Drawing the edge
      c << move_to(0, 0)
	<< m_arrow_colour
	<< line(width, 0)
	<< line(0, height)
	<< line(-width, 0)
	<< line(0, -height);

      // Drawing the arrow
      c << move_to(x_start, y_start)
	<< line(width * (1 - 2 * x_relative_padding) / 2,
		y_coeff * height * (1 - 2 * y_relative_padding))
	<< line(width * (1 - 2 * x_relative_padding) / 2,
		-y_coeff * height * (1 - 2 * y_relative_padding));
    }

  
  private:
    DIRECTION m_dir;
    genv::color m_arrow_colour;
  };

  
  TextBox *m_text_box;
  ArrowButton *m_arrow_up;
  ArrowButton *m_arrow_down;

  std::shared_ptr< SpinnerModel<T> > m_model;
};

} // namespace wl

#endif // SPINNER_HPP
