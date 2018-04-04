#include "BorderLayout.hpp"
#include <curses.h> //wresize
#include "../windows/WindowHandleWindow.hpp"

namespace curses {
  
  std::vector<curses::WindowHandleWindow *> BorderLayout::
    getDirectlyContainedWindows() const
  {
    std::vector<curses::WindowHandleWindow *> vec;
    for( containerType::const_iterator citer = m_area2WindowContainer.begin() ;
        citer != m_area2WindowContainer.end() ; citer ++ )
    {
      curses::WindowHandleWindow * p_window = citer->second;
      if( p_window != NULL )
        vec.push_back(p_window);
    }
    return vec;
  }
  
  /** see https://docs.oracle.com/javase/7/docs/api/java/awt/BorderLayout.html
   *  +------------------+
   *  |     top panel    |
   *  +-----+------+-----+
   *  |left |center|right|
   *  |panel|panel |panel|
   *  +-----+------+-----+
   *  |    bottom panel  |
   *  +------------------+ */
  void BorderLayout::GetMinimalSize(int & width, int & height)
  {
    width = 0;
    height = 0;
    int topWidth, bottomWidth;
    containerType::const_iterator topIter = m_area2WindowContainer.find(top);
    if( topIter != m_area2WindowContainer.end() )
    {
      int _width, _height;
      topIter->second->GetMinimalSize(_width, _height);
      topWidth = _width;
      height += _height;
    }
    containerType::const_iterator centerIter = m_area2WindowContainer.find(center);
    if( centerIter != m_area2WindowContainer.end() )
    {
      int _width, _height;
      curses::WindowHandleWindow * p_win = centerIter->second;
      centerIter->second->GetMinimalSize(_width, _height);
      height += _height;
      width += _width;
    }
    containerType::const_iterator bottomIter = m_area2WindowContainer.find(bottom);
    if( bottomIter != m_area2WindowContainer.end() )
    {
      int _width, _height;
      bottomIter->second->GetMinimalSize(_width, _height);
      height += _height;
    }
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
    int upperLeftCorner1stColumn, upperLeftCorner1stRow;
    getbegyx(m_windowHandle, upperLeftCorner1stRow, upperLeftCorner1stColumn);
    int currentHorizontalPos = upperLeftCorner1stColumn, currentVerticalPos = upperLeftCorner1stRow;
    
    wrefresh(m_windowHandle);
    containerType::const_iterator topIter = m_area2WindowContainer.find(top);
    if( topIter != m_area2WindowContainer.end() )
    {
      curses::WindowHandleWindow * window = topIter->second;
      WINDOW * windowHandle = window->getWindowHandle();
      wresize(windowHandle, 1/*lines*/, maxx/*columns*/);
      mvwin(windowHandle, /*upper left y*/ currentVerticalPos, /*upper left x*/currentHorizontalPos);
      wrefresh(windowHandle);
      //TODO add getMinimalSize())'s height to currentVerticalPos
      currentVerticalPos ++;
      window->doLayout();
    }
    containerType::const_iterator leftIter = m_area2WindowContainer.find(left);
    int centerWidth = maxx;
    if( leftIter != m_area2WindowContainer.end() )
    {
      curses::WindowHandleWindow * window = leftIter->second;
      WINDOW * windowHandle = window->getWindowHandle();
      //TODO add getMinimalSize())'s height to currentVerticalPos
      int minWidth, minHeight;
      window->GetMinimalSize(minWidth, minHeight);
      wresize(windowHandle, minHeight/*lines*/, minWidth/*columns*/);
      mvwin(windowHandle, /*upper left y*/ currentVerticalPos, /*upper left x*/currentHorizontalPos);      
      currentHorizontalPos += minWidth;
      centerWidth -= minWidth;
      window->doLayout();
      wrefresh(windowHandle);
    }
    containerType::const_iterator rightIter = m_area2WindowContainer.find(right);
    if( rightIter != m_area2WindowContainer.end() )
    {
      curses::WindowHandleWindow * window = rightIter->second;
      WINDOW * windowHandle = window->getWindowHandle();
      //TODO add getMinimalSize())'s height to currentVerticalPos
      int minWidth, minHeight;
      window->GetMinimalSize(minWidth, minHeight);
      wresize(windowHandle, minHeight/*lines*/, minWidth/*columns*/);
      centerWidth -= minWidth;
      mvwin(windowHandle, /*upper left y*/ currentVerticalPos, 
        /*upper left x*/currentHorizontalPos + centerWidth);
      window->doLayout();
      wrefresh(windowHandle);
    }
    
    containerType::const_iterator bottomIter = m_area2WindowContainer.find(bottom);
    containerType::const_iterator centerIter = m_area2WindowContainer.find(center);
    if( centerIter != m_area2WindowContainer.end() )
    {
      int verticalSize = maxy;
      if( topIter != m_area2WindowContainer.end() )
        //TODO subtract getMinimalSize())'s height from verticalSize;
        verticalSize --;
      if( bottomIter != m_area2WindowContainer.end() )
        //TODO subtract getMinimalSize())'s height from verticalSize;
        verticalSize --;
      WINDOW * windowHandle = centerIter->second->getWindowHandle();
      wresize(windowHandle, verticalSize /*lines*/, centerWidth /*columns*/);
      /** move window */
      mvwin(windowHandle, /*upper left y*/currentVerticalPos, 
        /*upper left x*/currentHorizontalPos);
      currentVerticalPos += verticalSize;
      wrefresh(windowHandle);
    }
    if( bottomIter != m_area2WindowContainer.end() )
    {
      curses::WindowHandleWindow * window = bottomIter->second;
      int width, height;
      window->GetMinimalSize(width, height);
      WINDOW * windowHandle = window->getWindowHandle();
      wresize(windowHandle, 1/*lines*/, maxx/*columns*/);
//      int minHeight = window->GetMinimalSize();
      //TODO subtract getMinimalSize())'s height from verticalSize;
      mvwin(windowHandle, /*upper left y*/ currentVerticalPos, /*upper left x*/currentHorizontalPos);
      window->doLayout();
      wrefresh(windowHandle);
    }
  }
}
