#include "PercentalLayout.hpp"

namespace curses {

curses::LayoutManagerBase::windowsContainerType PercentalLayout::
  getDirectlyContainedWindows() const
{
  curses::LayoutManagerBase::windowsContainerType windows;
  for( std::vector<curses::WindowHandleWindowAndPercentage>::const_iterator 
    iter = m_windows.begin() ; iter != m_windows.end(); iter++ )
  {
//    if (dynamic_cast<D2*>(x) == nullptr)
//    if( iter->m_p->IsUIcontrol() )
    {
       windows.push_back(iter->m_p);
    }
  }
  return windows;
}

void PercentalLayout::layout()
{
  std::vector<curses::WindowHandleWindowAndPercentage>::const_iterator iter = 
    m_windows.begin();
  
  int maxy;
  int maxx;
#ifdef PDCURSES
  maxy = getmaxy(m_windowHandle);
  maxx = getmaxx(m_windowHandle);
#else
  getmaxyx(m_windowHandle, maxy, maxx);
#endif
  int y_begin, x_begin;
  getbegyx(m_windowHandle, y_begin, x_begin);

  int horizontalSize, verticalSize;
  int currentHorizontalPos = x_begin, currentVerticalPos = y_begin;
  for( ; iter != m_windows.end(); iter ++ )
  {
    const WindowHandleWindowAndPercentage & windowHandleWindowAndPercentage = *iter;
    WINDOW * windowHandle = windowHandleWindowAndPercentage.m_p->getWindowHandle();
    if(m_direction == horizontal )
    {
      horizontalSize = (int) (windowHandleWindowAndPercentage.m_percent * (float) maxx);
      verticalSize = maxy;
    }
    else
    {
      horizontalSize = maxx;
      verticalSize =  (int) (windowHandleWindowAndPercentage.m_percent * (float) maxy);
    }
    wresize(windowHandle, verticalSize, horizontalSize);
    mvwin(windowHandle, currentVerticalPos, currentHorizontalPos); /** move window */
    wrefresh(windowHandle);
    if(m_direction == horizontal )
      currentHorizontalPos += horizontalSize;
    else
      currentVerticalPos += verticalSize;
    windowHandleWindowAndPercentage.m_p->doLayout();
  }
}


}
