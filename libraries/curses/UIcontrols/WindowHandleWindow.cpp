#include "WindowHandleWindow.hpp"
#include "../LayoutManager/LayoutManagerBase.hpp"

namespace Curses {

void WindowHandleWindow::create()
{
  handle = newwin(1, 1, 0, 0);
}

void WindowHandleWindow::setLayout(curses::LayoutManagerBase * p_layoutManager)
{ 
  mp_layoutManager = p_layoutManager;
  mp_layoutManager->setHandle(handle);
}

void WindowHandleWindow::doLayout() const
{
  if(mp_layoutManager)
  {
    mp_layoutManager->layout();
  }
}
}

