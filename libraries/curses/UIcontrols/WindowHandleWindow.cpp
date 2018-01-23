#include "WindowHandleWindow.hpp"
#include "../LayoutManager/LayoutManagerBase.hpp"

namespace Curses {

void WindowHandleWindow::create()
{
  handle = newwin(1, 1, 0, 0);
}

void WindowHandleWindow::doLayout() const
{
  if(mp_layoutManager)
  {
    mp_layoutManager->layout();
  }
}
}

