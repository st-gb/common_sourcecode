#include <stdint.h>

#include "Window.hpp"
#include "../EventQueue.hpp"///class EventQueue
#include "WindowHandleWindow.hpp"///class WindowHandleWindow
//#include <typeinfo>///typeid

curses::InputProcessorStack Curses::Window::s_inputProcessorStack;
extern curses::EventQueue g_eventQueue;

namespace Curses//TODO make lower case? (because of proper name "curses")
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
    Curses::Window * p_foremostWinHandleWin = Window::s_inputProcessorStack.
      getForemostWinHandleWin();
    int key;
    ///https://en.wikibooks.org/wiki/C%2B%2B_Programming/Programming_Languages/C%2B%2B/Code/Keywords/typeid
    if( /*typeid(p_last) == typeid(curses::WindowHandleWindow)*/ 
      p_foremostWinHandleWin )
    {
      key = wgetch( ((curses::WindowHandleWindow *)p_foremostWinHandleWin)->
        getWindowHandle() );
    }
    else
    //Sometimes (ncurses 5--6.1-1ubuntu1.18.04) makes all windows black if
    /// called.
    // see https://stackoverflow.com/questions/19748685/curses-library-why-does-getch-clear-my-screen
    /// "getch() does an implicit refresh()"
      key = getch();
    if( key != ERR )///"ERR" if no key was pressed
      ///Can't do a "if(p_last) p_last->HandleAction(...)" instead because
      /// top level windows should also be able to receive keys.
      Window::s_inputProcessorStack.consume(key);
    if( processEventQueue)
      g_eventQueue.Process();
  }while(! Window::s_inputProcessorStack.exit );
}
}
