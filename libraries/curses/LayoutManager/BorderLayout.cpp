#include "BorderLayout.hpp"
#include <curses.h> //wresize
#include "../windows/WindowHandleWindow.hpp"

namespace curses {
  
  std::vector<ncurses::WindowHandleWindow *> BorderLayout::
    getDirectlyContainedWindows() const
  {
    //TODO implement
    return std::vector<ncurses::WindowHandleWindow *>();
  }
  
  void BorderLayout::layout()
  {
    int maxy;
    int maxx;
#ifdef PDCURSES
    maxy = getmaxy(m_windowHandle);
    maxx = getmaxx(m_windowHandle);
#else
    getmaxyx(m_windowHandle, maxy, maxx);
#endif
    wrefresh(m_windowHandle);
    containerType::const_iterator topIter = m_area2WindowContainer.find(top);
    if( topIter != m_area2WindowContainer.end() )
    {
      wresize(topIter->second->getWindowHandle(), 1/*lines*/, maxx/*columns*/);
      wrefresh(topIter->second->getWindowHandle());
    }
    containerType::const_iterator centerIter = m_area2WindowContainer.find(center);
    if( centerIter != m_area2WindowContainer.end() )
    {
      int verticalSize = maxy;
      if( topIter != m_area2WindowContainer.end() )
        verticalSize --;
      WINDOW * windowHandle = centerIter->second->getWindowHandle();
      wresize(windowHandle, verticalSize /*lines*/, maxx /*columns*/);
      if( topIter != m_area2WindowContainer.end() )
        mvwin(windowHandle, /*upper left y*/1, /*upper left x*/0); /** move window */
      else
        mvwin(windowHandle, /*upper left y*/0, /*upper left x*/0); /** move window */        
      wrefresh(windowHandle);
    }
  }
}
