#pragma once //Include guard, more resource-saving than a #ifdef ... include guard

#ifndef LIBARIES_NCURSES_INPUTPROCESSORSTACK_HPP
#define LIBARIES_NCURSES_INPUTPROCESSORSTACK_HPP

#include <vector> //class std::vector
#include <deque> //class std::deque

//#include "windows/WindowHandleWindow.hpp"

/** Forward declarations (faster than to include the header file) : */
namespace Curses{
  class Window;
}
namespace ncurses {
  class WindowHandleWindow;
}

namespace ncurses
{
  /** This class serves the following purpose: 
    * The window that has the current focus should not be responsible to handle
    * all possible events (e.g. also TERMINAL_RESIZE).
    * The "ncurses" window that is created first is the bottom of the stack. 
    * Usually also this window should handle TERMINAL_RESIZE events. 
    * Instead of the text input etc. windows that are created afterwards. */
  class InputProcessorStack
  {
    /** Need to use a sequence container here, beause the order of the 
     *  elements is important.
     *  See https://www.cs.helsinki.fi/u/tpkarkka/alglib/k06/lectures/containers.html
     * "Sequences: User controls the order of elements.
     *   vector, list, deque" */
    typedef std::deque<Curses::Window *> container_type;
    private:
//    std::vector<Ncurses::Window *> m_inputProcessorStack;
      /** Use a double-ended queue (deque) because the container should be
       *  accessed from the back (last element). */
    container_type m_inputProcessorStack;
  public:
    InputProcessorStack() : exit(false) {}
    void add(Curses::Window * w) { m_inputProcessorStack.push_back(w); }
    void RemoveLastElement() { m_inputProcessorStack.pop_back(); }
    void UpdateAllWindowsHiddenBy(const ncurses::WindowHandleWindow *);
    void consume(const int ch);
    bool exit;
  };
}

#endif //#ifndef LIBARIES_NCURSES_INPUTPROCESSORSTACK_HPP
