#include "BorderLayout.hpp"
#include <curses.h> //wresize
#include "../UIcontrols/WindowHandleWindow.hpp"

namespace curses {
  void BorderLayout::layout()
  {
    int maxy;
#ifdef PDCURSES
    maxy = getmaxy(windowToSetColourTo);
#else
    int maxx;
    getmaxyx(m_windowHandle, maxy, maxx);
#endif
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
      mvwin(windowHandle, 1, 0);
      wrefresh(centerIter->second->getWindowHandle());
    }    
    wrefresh(m_windowHandle);
  }
}
