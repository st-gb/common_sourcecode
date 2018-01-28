#pragma once
#include <curses.h> //WINDOW
//#include "../LayoutManager/LayoutManagerBase.hpp"

namespace curses { class LayoutManagerBase; }

namespace Curses {
/** Class that encapsulates a curses WINDOW pointer/handle. */
class WindowHandleWindow
{
protected: /** To inherit to subclasses. */
  WINDOW * handle;
//  std::vector<WindowHandleWindow *> m_windows;
  curses::LayoutManagerBase * mp_layoutManager;
public:
  WindowHandleWindow() : handle(NULL), mp_layoutManager(NULL) { }
  void setLayout(curses::LayoutManagerBase * p_layoutManager);
  void doLayout() const;
  void create();
  WINDOW * getWindowHandle() const { return handle;}
//  void add(WindowHandleWindow & win, float percent) { m_windows.push_back(&win);}
};
}
