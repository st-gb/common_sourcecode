#pragma once
//#include "Window.hpp" //base class
#include "WindowHandleWindow.hpp"//base class

namespace curses {
/** Class name and subclass hierarchy is inspired by wxWidgets. */
class TopLevelWindow
  : public Curses::WindowHandleWindow
{
public:
  int HandleAction(const int ch);
};

}

