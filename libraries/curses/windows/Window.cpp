#include <stdint.h>

#include "Window.hpp"
#include "../EventQueue.hpp" //class EventQueue

curses::InputProcessorStack Curses::Window::s_inputProcessorStack;
extern curses::EventQueue g_eventQueue;

namespace Curses
{
  WINDOW * Window::CreateWindowRelativePos(
    WINDOW * p_windowForRelativePos,
    int heightInLines, 
    int widthInColumns,
    int yPosRelativeToReferredWindow, 
    int xPosRelativeToReferredWindow)
  {
    /** http://pubs.opengroup.org/onlinepubs/7908799/xcurses/doupdate.html
    * "refresh the current or specified window." */
    //wrefresh(p_superWindow);
    int upperLeftCorner1stColumn, upperLeftCorner1stRow;
    //getyx(p_windowForRelativePos, cury, curx);
    getbegyx(p_windowForRelativePos, upperLeftCorner1stColumn, upperLeftCorner1stRow);
    //see https://linux.die.net/man/3/newwin
    return newwin(
      heightInLines, /** # of lines */
      widthInColumns /** number of colums */, 
      yPosRelativeToReferredWindow + upperLeftCorner1stColumn /** begin_y */,
      xPosRelativeToReferredWindow + upperLeftCorner1stRow /** begin_x */ );
  }
  
//  void * Window::operator new(std::size_t size)
//  {
//    m_allocatedOnHeap = true;
//    void * addressOfAllocatedMemory = new uint8_t[size];
//    return addressOfAllocatedMemory;
//  }
  
  void EventLoop(bool processEventQueue)
  {
    do
    {
      //TODO sometimes makes all windows black if called
      // see https://stackoverflow.com/questions/19748685/curses-library-why-does-getch-clear-my-screen
      int key = getch();
      if( key != ERR )
        Window::s_inputProcessorStack.consume(key);
      if( processEventQueue)
        g_eventQueue.Process();
    }while(! Window::s_inputProcessorStack.exit );
  }
}
