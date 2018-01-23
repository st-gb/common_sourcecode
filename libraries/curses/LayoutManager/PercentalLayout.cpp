#include "PercentalLayout.hpp"

namespace curses {

void PercentalLayout::layout()
{
  std::vector<curses::WindowHandleWindowAndPercentage>::const_iterator iter = 
    m_windows.begin();
  
  int maxy;
#ifdef PDCURSES
  maxy = getmaxy(windowToSetColourTo);
#else
  int maxx;
  getmaxyx(m_windowHandle, maxy, maxx);
#endif

  int horizontalSize, verticalSize;
  int currentHorizontalPos = 0, currentVerticalPos = 0;
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
    mvwin(windowHandle, currentVerticalPos, currentHorizontalPos);
    wrefresh(windowHandle);
    if(m_direction == horizontal )
      currentHorizontalPos += horizontalSize;
    else
      currentVerticalPos += verticalSize;
    windowHandleWindowAndPercentage.m_p->doLayout();
  }
}
}
