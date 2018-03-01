#include "EventQueue.hpp" //class EventQueue
#include "GetChar.hpp"
#include <curses.h> //wgetch(...), WINDOW

extern ncurses::EventQueue g_eventQueue;

namespace ncurses
{
  /** In order to enable processing of events from other threads this 
    function must be called from User Interface code. */
  int GetChar(WINDOW * p_window) {
    int ch = wgetch(p_window);
    if(ch == ERR)
    {
      g_eventQueue.Process();
    }
    return ch;
  }
}
