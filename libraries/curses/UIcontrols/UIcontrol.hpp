#pragma once /** Include guard. */

//#include "Window.hpp"
#include "WindowHandleWindow.hpp" //base class WindowHandleWindow

namespace curses {
class UIcontrol
  : public Curses::WindowHandleWindow
{
protected:
  bool m_hasFocus;
public:
  UIcontrol() 
    : Curses::WindowHandleWindow(true)
    , m_hasFocus(false) {}
  bool HasFocus() const { return m_hasFocus;}
  virtual void SetFocus(bool focus) { 
    m_hasFocus = focus;}
};
}
