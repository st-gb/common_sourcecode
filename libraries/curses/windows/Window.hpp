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
//    bool m_allocatedOnHeap;
  public:
    /** "static"-> 1 stack for all objects of class "Window" and its 
     *   descendants;not thread-safe: */
    static curses::InputProcessorStack s_inputProcessorStack;
    Window() : m_isUIcontrol(false)//, m_allocatedOnHeap(false) 
      {}
    Window(bool isUIcontrol) : m_isUIcontrol(isUIcontrol) {}
    virtual ~Window() {}
    
//    void * operator new(std::size_t size);
    enum handleActionRetCodes { destroyWindow = -2, inputNotHandled = -1 };
    /** Must be "virtual" in order to enable overriding. */
    virtual int HandleAction(const int ch) { return 0; }
    static WINDOW * CreateWindowRelativePos(WINDOW * windowForRelativePos,
      int width, int height, int ypos, int xpos);
    /** Declared in this class because also non-handle window classes should
        be usable in layout managers as "spacers". */
    virtual void GetMinimalSize(int & width, int & height){width = 1; height = 1;}
    bool IsUIcontrol() const { return m_isUIcontrol;}
  };
  
  void EventLoop(bool processEventQueue);
}
