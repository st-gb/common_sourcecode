#pragma once //
#include <curses.h>

namespace curses
{
  class LayoutManagerBase
  {
  protected:
    /** The window handle for the window this layout manager is attached to. */
    WINDOW * m_windowHandle;
  public:
    virtual void layout() = 0;
    void setHandle(WINDOW * windowHandle) { m_windowHandle = windowHandle;}
  };
}
