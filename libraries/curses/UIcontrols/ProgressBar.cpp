/** File:   ProgressBar.cpp
 * Author: sg
 * Created on 7. April 2018, 12:42 */

#include "ProgressBar.hpp"
#include <limits.h>//INT_MAX

namespace curses {

void ProgressBar::show()
{
  int maxy;
  int maxx;
  /** Erase all content from before. */
  wclear(m_windowHandle);
  setcolor(m_windowHandle, m_colorPair);
#ifdef PDCURSES
  maxy = getmaxy(m_windowHandle);
  maxx = getmaxx(m_windowHandle);
#else
  getmaxyx(m_windowHandle, maxy, maxx);
#endif
  float f = m_progress / INT_MAX;
  int progressRelativeToWindowWidth = f * maxx;
  for(int xIndex = 0; xIndex < progressRelativeToWindowWidth; xIndex ++)
  {
    mvwaddch(m_windowHandle, 0, xIndex, ACS_CKBOARD);
  }
  for(int xIndex = progressRelativeToWindowWidth; xIndex < maxx; xIndex ++)
  {
    mvwaddch(m_windowHandle, 0, xIndex, ' ');
  }
  /** Finally update visually. */
  wrefresh(m_windowHandle);
}

}