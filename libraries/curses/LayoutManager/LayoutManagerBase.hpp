#pragma once /** Include guard. */
#include <curses.h> //WINDOW
#include "../windows/WindowHandleWindow.hpp" //base class WindowHandleWindow
#include "../UIcontrols/UIcontrol.hpp"

//#include "PercentalLayout.hpp"

namespace curses
{
  /** Forward declarations */
//  class WindowHandleWindow;
  
  class LayoutManagerBase
    : public Curses::WindowHandleWindow
  {
  protected:
    /** The window handle for the window this layout manager is attached to. */
//    WINDOW * m_windowHandle;
  public:
    virtual void layout() = 0;
    /** Let the container be a vector because this is a simple container, */
    virtual std::vector<Curses::WindowHandleWindow *> 
        getDirectlyContainedWindows() const = 0;
    std::vector<Curses::WindowHandleWindow *> getAllContainedWindows() const;
    
    curses::UIcontrol * getNextUIcontrolHavingFocus();
    void setHandle(WINDOW * windowHandle) { //m_windowHandle = windowHandle;
        m_windowHandle = windowHandle; }
    void SetFocusToNextUIcontrol();
//    /*curses::UIcontrol*/ Curses::WindowHandleWindow * getUIcontrolHavingFocus() const;
  };
}
