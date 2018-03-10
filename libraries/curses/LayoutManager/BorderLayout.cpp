#include "BorderLayout.hpp"
#include <curses.h> //wresize
#include "../windows/WindowHandleWindow.hpp"

namespace curses {
  
  std::vector<ncurses::WindowHandleWindow *> BorderLayout::
    getDirectlyContainedWindows() const
  {
    std::vector<ncurses::WindowHandleWindow *> vec;
    for( containerType::const_iterator citer = m_area2WindowContainer.begin() ;
        citer != m_area2WindowContainer.end() ; citer ++ )
    {
      ncurses::WindowHandleWindow * p_window = citer->second;
      if( p_window != NULL )
        vec.push_back(p_window);
    }
    return vec;
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
    containerType::const_iterator bottomIter = m_area2WindowContainer.find(bottom);
    if( bottomIter != m_area2WindowContainer.end() )
    {
      ncurses::WindowHandleWindow * window = bottomIter->second;
      WINDOW * windowHandle = window->getWindowHandle();
      wresize(windowHandle, 1/*lines*/, maxx/*columns*/);
//      int minHeight = window->GetMinimalSize();
      //TODO subtract getMinimalSize())'s height from verticalSize;
      mvwin(windowHandle, /*upper left y*/ maxy - 1, /*upper left x*/0);
      wrefresh(windowHandle);
    }
    containerType::const_iterator centerIter = m_area2WindowContainer.find(center);
    if( centerIter != m_area2WindowContainer.end() )
    {
      int verticalSize = maxy;
      if( topIter != m_area2WindowContainer.end() )
        verticalSize --;
      if( bottomIter != m_area2WindowContainer.end() )
        //TODO subtract getMinimalSize())'s height from verticalSize;
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
