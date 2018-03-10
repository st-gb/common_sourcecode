#include "WindowHandleWindow.hpp"
#include "../LayoutManager/LayoutManagerBase.hpp"

namespace ncurses {

void WindowHandleWindow::create()
{
  m_windowHandle = newwin(1, 1, 0, 0);
}

/** Update all windows that are affected by win (i.e. win lies in these 
 *  windows)*/
void WindowHandleWindow::UpdateAffectedWindows(WINDOW * win)
{
  if(mp_layoutManager)
  {
    std::vector<ncurses::WindowHandleWindow *> allWindows = mp_layoutManager->getAllContainedWindows();
    for( std::vector<ncurses::WindowHandleWindow *>::const_iterator iter = allWindows.begin(); 
      iter != allWindows.end() ; iter ++)
    {
      WINDOW * p_Window = (*iter)->m_windowHandle;
      /** https://linux.die.net/man/3/wrefresh */
      touchwin(p_Window);
      wrefresh(p_Window);
//      wnoutrefresh(iter->m_windowHandle)
    }
  }
}

void WindowHandleWindow::create(
  WINDOW * const p_superWindow, 
  int numLines, int numColumns, int x, int y)
{
//  m_p_superWindow = p_superWindow;
//  int cury, curx, begy, begx;
  /** http://pubs.opengroup.org/onlinepubs/7908799/xcurses/doupdate.html
  * "refresh the current or specified window." */
  wrefresh(p_superWindow);
//  getyx(p_superWindow, cury, curx);
//  getbegyx(p_superWindow, begy, begx);
  /** If window was created with derwin(...) or subwin(...) it isn't cleared
   *  from screen after wdelete(...). So use newwin(...) instead. */
  /*p_editWindow*/ m_windowHandle = //subwin( p_superWindow,
    Curses::Window::CreateWindowRelativePos(
    p_superWindow,
    numLines,
    numColumns /* number of colums */, 
    y, //begy + cury,
    x //begx + curx
    );
  //TODO is NULL when (indirectly) called from changePartitionTableOffsets(...)
  if( ! /*p_editWindow*/ m_windowHandle )
    return;
}

void WindowHandleWindow::setLayout(curses::LayoutManagerBase * p_layoutManager)
{ 
  mp_layoutManager = p_layoutManager;
  mp_layoutManager->setHandle(m_windowHandle);
}

/** Can be called after resizing a window. */
void WindowHandleWindow::doLayout() const
{
  if(mp_layoutManager)
  {
    mp_layoutManager->layout();
  }
}

void WindowHandleWindow::GetSize(int & width, int & height) const
{
  getmaxyx(m_windowHandle, height, width);
}

void WindowHandleWindow::RemoveAsKeyListener()
{
  //TODO iterate over container until this object found.
  s_inputProcessorStack.RemoveLastElement();  
}

void WindowHandleWindow::SetAsKeyListener()
{
  s_inputProcessorStack.add(this);
}

void WindowHandleWindow::SetFocusToNextUIcontrol()
{
  if(mp_layoutManager)
    mp_layoutManager->SetFocusToNextUIcontrol();
}
} /** Namespace curses */

