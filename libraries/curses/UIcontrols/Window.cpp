#include "Window.hpp"

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
      yPosRelativeToReferredWindow + upperLeftCorner1stColumn,
      xPosRelativeToReferredWindow + upperLeftCorner1stRow);
  }
   
  void EventLoop()
  {
    do
    {
      int key = getch();
      if( key != ERR )
        Window::s_inputProcessorStack.consume(key);
    }while(! Window::s_inputProcessorStack.exit );
  }
}
