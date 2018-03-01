#pragma once
#include <curses.h> //WINDOW
//#include "../LayoutManager/LayoutManagerBase.hpp"
#include "Window.hpp"

namespace curses { class LayoutManagerBase; }

namespace ncurses {
/** Class that encapsulates a curses WINDOW pointer/handle. */
class WindowHandleWindow
  : /** For ability to process key events */ 
    public Curses::Window
{
protected: /** To inherit to subclasses. */
  WINDOW * m_windowHandle;
//  std::vector<WindowHandleWindow *> m_windows;
  curses::LayoutManagerBase * mp_layoutManager;
public:
  WindowHandleWindow() : m_windowHandle(NULL), mp_layoutManager(NULL) { }
  WindowHandleWindow(bool isUIcontrol) : Curses::Window(isUIcontrol), 
    m_windowHandle(NULL), mp_layoutManager(NULL) { }
  void setLayout(curses::LayoutManagerBase * p_layoutManager);
  void doLayout() const;
  void create();
  void create(WINDOW * const p_superWindow, int numLines, int numColumns, 
    int x, int y);
  WINDOW * getWindowHandle() const { return m_windowHandle;}
  void GetSize(int & width, int & height) const;
  curses::LayoutManagerBase * getLayoutManager() const{return mp_layoutManager;}
  void RemoveAsKeyListener();
  void SetAsKeyListener();
  void SetFocusToNextUIcontrol();
//  void add(WindowHandleWindow & win, float percent) { m_windows.push_back(&win);}
};
}
