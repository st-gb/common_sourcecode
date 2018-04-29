#include "BorderLayout.hpp"
#include <curses.h> //wresize
#include "../windows/WindowHandleWindow.hpp"

namespace curses {
  
  curses::LayoutManagerBase::windowsContainerType BorderLayout::
    getDirectlyContainedWindows() const
  {
    windowsContainerType vec;
    for( containerType::const_iterator citer = m_area2WindowContainer.begin() ;
        citer != m_area2WindowContainer.end() ; citer ++ )
    {
      Curses::Window * p_window = citer->second;
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
      Curses::Window * p_win = centerIter->second;
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

  int HandleVerticalItem(
    Curses::Window * p_cursesWindow,
    int currentVerticalPos, 
    int currentHorizontalPos,
    int & centerItemVerticalSize,
    int maximumWidth,
    enum curses::BorderLayout::area area)
  {
    int minimalWidth, minimalHeight;
    p_cursesWindow->GetMinimalSize(minimalWidth, minimalHeight);
    centerItemVerticalSize -= minimalHeight;
    curses::WindowHandleWindow * window = dynamic_cast<curses::WindowHandleWindow *>(p_cursesWindow);
    if(window)
    {
      int upperLeftY = currentVerticalPos;
      if( area == curses::BorderLayout::bottom)
        upperLeftY += centerItemVerticalSize;
      WINDOW * windowHandle = window->getWindowHandle();
      wresize(windowHandle, minimalHeight/*lines*/, maximumWidth/*columns*/);
      mvwin(windowHandle, /*upper left y*/ upperLeftY, /*upper left x*/currentHorizontalPos);
      //TODO add getMinimalSize())'s height to currentVerticalPos
//      currentVerticalPos += minimalHeight;
      window->doLayout();
      wrefresh(windowHandle);
    }
    return minimalHeight;
  }
  
  int HandleHorizontalItem(
    Curses::Window * p_cursesWindow,
    int & currentVerticalPos, 
    int currentHorizontalPos,
    int & centerItemWidth,
    int maximumHeight,
    enum curses::BorderLayout::area area)
  {
    int minimalWidth, minimalHeight;
    p_cursesWindow->GetMinimalSize(minimalWidth, minimalHeight);
    currentHorizontalPos += minimalWidth;
    centerItemWidth -= minimalWidth;
    
    curses::WindowHandleWindow * window = dynamic_cast<curses::WindowHandleWindow *>(p_cursesWindow);
    if(window)
    {
      int upperLeftX = currentHorizontalPos;
      if( area == curses::BorderLayout::right)
        upperLeftX += centerItemWidth;
      WINDOW * windowHandle = window->getWindowHandle();
      wresize(windowHandle, maximumHeight/*lines*/, minimalWidth/*columns*/);
      mvwin(windowHandle, /*upper left y*/ currentVerticalPos, /*upper left x*/upperLeftX);
      //TODO add getMinimalSize())'s height to currentVerticalPos
      window->doLayout();
      wrefresh(windowHandle);
    }
    return minimalWidth;
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
    int centerItemVerticalSize = maxy;
    int centerItemWidth = maxx;
    int upperLeftCorner1stColumn, upperLeftCorner1stRow;
    getbegyx(m_windowHandle, upperLeftCorner1stRow, upperLeftCorner1stColumn);
    int currentHorizontalPos = upperLeftCorner1stColumn, currentVerticalPos = upperLeftCorner1stRow;
    wclear(m_windowHandle);
//    wrefresh(m_windowHandle);
    containerType::const_iterator topIter = m_area2WindowContainer.find(top);
    if( topIter != m_area2WindowContainer.end() )
    {
      currentVerticalPos += HandleVerticalItem(
        topIter->second,
        upperLeftCorner1stRow,
        upperLeftCorner1stColumn,
        centerItemVerticalSize,
        maxx,
        curses::BorderLayout::top);
    }
    containerType::const_iterator bottomIter = m_area2WindowContainer.find(bottom);
    if( bottomIter != m_area2WindowContainer.end() )
    {
      HandleVerticalItem(bottomIter->second, upperLeftCorner1stRow, upperLeftCorner1stColumn,
        centerItemVerticalSize, maxx, curses::BorderLayout::bottom);
    }
    containerType::const_iterator leftIter = m_area2WindowContainer.find(left);
    int centerWidth = maxx;
    int centerLeftXpos = upperLeftCorner1stColumn;
    if( leftIter != m_area2WindowContainer.end() )
    {
      centerLeftXpos = HandleHorizontalItem(leftIter->second, currentVerticalPos, 
        currentHorizontalPos, centerItemWidth, centerItemVerticalSize,
        curses::BorderLayout::left);
    }
    containerType::const_iterator rightIter = m_area2WindowContainer.find(right);
    if( rightIter != m_area2WindowContainer.end() )
    {
      HandleHorizontalItem(rightIter->second, currentVerticalPos, 
        currentHorizontalPos, centerItemWidth, centerItemVerticalSize,
        curses::BorderLayout::right);
    }
    containerType::const_iterator centerIter = m_area2WindowContainer.find(center);
    if( centerIter != m_area2WindowContainer.end() )
    {
      curses::WindowHandleWindow * p_windowHandleWindow = dynamic_cast<
        curses::WindowHandleWindow *>(centerIter->second);
      if(p_windowHandleWindow)
      {
        WINDOW * windowHandle = p_windowHandleWindow->getWindowHandle();
        wresize(windowHandle, centerItemVerticalSize /*lines*/, centerItemWidth /*columns*/);
        /** move window */
        mvwin(windowHandle, /*upper left y*/currentVerticalPos, 
          /*upper left x*/centerLeftXpos);
        /** the Window may be a layout manager. */
        p_windowHandleWindow->doLayout();
//        currentVerticalPos += verticalSize;
//      wrefresh(windowHandle);#
      }
    }
  }
}
