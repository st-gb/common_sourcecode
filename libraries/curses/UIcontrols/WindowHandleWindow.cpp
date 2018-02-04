#include "WindowHandleWindow.hpp"
#include "../LayoutManager/LayoutManagerBase.hpp"

namespace Curses {

void WindowHandleWindow::create()
{
  m_windowHandle = newwin(1, 1, 0, 0);
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
  {
    curses::UIcontrol * p_UIcontrol = mp_layoutManager->getNextUIcontrolHavingFocus();
    if( p_UIcontrol )
    {
      p_UIcontrol->SetFocus(true);
    }
  }
}
} /** Namespace curses */

