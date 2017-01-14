#pragma once//Include guard, more resource-saving than a #ifdef ... include guard

#include "InputProcessorStack.hpp"

namespace Ncurses
{
  /** Base class of all wrapper classes for ncurses controls. */
  class Window
  {
  protected:
    /** "static"-> 1 stack for all objects of class "Window" and its 
     *   descendants;not thread-safe: */
    static Ncurses::InputProcessorStack s_inputProcessorStack;
  public:
    enum handleActionRetCodes { inputNotHandled = -1 };
    /** Must be virtual in order to enable. */
    virtual int HandleAction(const int ch) { }
  };
}
