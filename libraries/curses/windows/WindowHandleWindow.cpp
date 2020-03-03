#include "WindowHandleWindow.hpp"
#include "../LayoutManager/LayoutManagerBase.hpp"
#include "../UIcontrols/TextBox.hpp"
#include "../LayoutManager/BorderLayout.hpp"

namespace curses {

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
    curses::LayoutManagerBase::windowsContainerType allWindows = mp_layoutManager->getAllContainedWindows();
    for( curses::LayoutManagerBase::windowsContainerType::const_iterator iter = allWindows.begin(); 
      iter != allWindows.end() ; iter ++)
    {
      curses::WindowHandleWindow * p_windowHandleWindow = dynamic_cast<
        curses::WindowHandleWindow *>(*iter);
      if( p_windowHandleWindow)
      {
        WINDOW * p_Window = p_windowHandleWindow->m_windowHandle;
        /** https://linux.die.net/man/3/wrefresh */
        touchwin(p_Window);
        wrefresh(p_Window);
  //      wnoutrefresh(iter->m_windowHandle)
      }
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

//TODO remove all windows if not as member (check is where address lies )
//RemoveAndDeleteAllWindows
//{
//  
//}

void WindowHandleWindow::destroyAllContainedWindows()
{
    if(mp_layoutManager)
    {
        mp_layoutManager->destroyAllContainedWindows();
        delete mp_layoutManager;
    }
}

void WindowHandleWindow::setLayout(curses::LayoutManagerBase * p_layoutManager)
{
//  wclear(m_windowHandle);
  //TODO before remove all windows?
//  if(mp_layoutManager)
//    RemoveAndDeleteAllWindows();
  mp_layoutManager = p_layoutManager;
  mp_layoutManager->setHandle(m_windowHandle);
}

/** Can be called after resizing a window. */
void WindowHandleWindow::doLayout() const
{
  wclear(m_windowHandle);
  curses::LayoutManagerBase * const p_layoutMan = (curses::LayoutManagerBase *)
    dynamic_cast<const curses::LayoutManagerBase * const >(this);
  if( p_layoutMan )
    p_layoutMan->layout();
  else
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
  //TODO iterate over container until _this_ object found.
//  s_inputProcessorStack.RemoveLastElement();
  s_inputProcessorStack.Remove(this);
}

///Only with a curses WINDOW handle it is possible to do a curses wgetch(...)
void WindowHandleWindow::SetAsKeyListener()
{
  s_inputProcessorStack.add(this);
}

void WindowHandleWindow::OutputText(const char text [], chtype colorPair)
{
//  if(mp_layoutManager)
  curses::BorderLayout * p_borderLayout = new curses::BorderLayout();
  p_borderLayout->create();
  setLayout(p_borderLayout);
  curses::TextBox * tb = new curses::TextBox(colorPair);
  tb->create(p_borderLayout->m_windowHandle, 0,0,1,1);
  tb->SetText(text);
  p_borderLayout->add(tb, BorderLayout::center);
  mp_layoutManager = p_borderLayout;
  p_borderLayout->doLayout();
  tb->show();
}

void WindowHandleWindow::SetFocusToNextUIcontrol()
{
  if(mp_layoutManager)
    mp_layoutManager->SetFocusToNextUIcontrol();
}
} /** Namespace curses */

