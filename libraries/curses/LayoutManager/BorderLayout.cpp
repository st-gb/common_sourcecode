#include "BorderLayout.hpp"
#include <curses.h> //wresize
#include "../windows/WindowHandleWindow.hpp"

namespace curses {
  
  std::vector<Curses::WindowHandleWindow *> BorderLayout::
    getDirectlyContainedWindows() const
  {
    //TODO implement
    return std::vector<Curses::WindowHandleWindow *>();
  }
  
  void BorderLayout::layout()
  {
    int maxy;
#ifdef PDCURSES
    maxy = getmaxy(windowToSetColourTo);
#else
    int maxx;
    getmaxyx(m_windowHandle, maxy, maxx);
#endif
    wrefresh(m_windowHandle);
    containerType::const_iterator topIter = m_area2WindowContainer.find(top);
    if( topIter != m_area2WindowContainer.end() )
    {
      wresize(topIter->second->getWindowHandle(), 1, maxx);
      wrefresh(topIter->second->getWindowHandle());
    }
    containerType::const_iterator centerIter = m_area2WindowContainer.find(center);
    if( centerIter != m_area2WindowContainer.end() )
    {
      int verticalSize = maxy;
      if( topIter != m_area2WindowContainer.end() )
        verticalSize --;
      WINDOW * windowHandle = centerIter->second->getWindowHandle();
      wresize(windowHandle, verticalSize, maxx);
      mvwin(windowHandle, 1, 0); /** move window */
      wrefresh(centerIter->second->getWindowHandle());
    }
  }
}
