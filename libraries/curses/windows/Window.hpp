#pragma once//Include guard, more resource-saving than a #ifdef ... include guard

#include "../InputProcessorStack.hpp"
#include <curses.h> //struct WINDOW

//forward declaration
//struct _win_st;
//typedef struct _win_st WINDOW;

namespace Curses
{
  //TODO: rename to: BasicUIcontrol?
  /** Base class of all wrapper classes for ncurses controls. */
  class Window
  {
  protected:
    bool m_isUIcontrol;
  public:
    /** "static"-> 1 stack for all objects of class "Window" and its 
     *   descendants;not thread-safe: */
    static Curses::InputProcessorStack s_inputProcessorStack;
    Window() : m_isUIcontrol(false) {}
    Window(bool isUIcontrol) : m_isUIcontrol(isUIcontrol) {}
    enum handleActionRetCodes { inputNotHandled = -1 };
    /** Must be "virtual" in order to enable overriding. */
    virtual int HandleAction(const int ch) { }
    static WINDOW * CreateWindowRelativePos(WINDOW * windowForRelativePos,
      int width, int height, int ypos, int xpos);
    bool IsUIcontrol() const { return m_isUIcontrol;}
  };
  
  void EventLoop();
}
