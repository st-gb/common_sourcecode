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
    /** Inherits from WindowHandleWindow because:
     *  -a layout manager may contain another layout manager
     *  -has a window handle */
    : public curses::WindowHandleWindow
  {
  protected:
//    /** The window handle for the window this layout manager is attached to. 
//        Must not be deleted via delwin because it belongs to a WindowHandleWindow. 
//        The pointer is just a copy. */
//    WINDOW * m_windowHandle;
    /** If the window handle is a reference or not */
    bool m_bReference;
  public:
    LayoutManagerBase() : m_bReference(false) {}
    ~LayoutManagerBase() {
      if( m_bReference )
        /** Prevent destructor ~curses::WindowHandleWindow() from calling 
         *  delwin(...) for this window handle. */
        m_windowHandle = NULL;
    }
    typedef std::vector<Curses::Window *> windowsContainerType;
    void create() {
       m_bReference = false;
       curses::WindowHandleWindow::create();
    }
    virtual void layout() = 0;
    void destroyAllContainedWindows();
    /** Let the container be a vector because this is a simple container, */
    virtual windowsContainerType getDirectlyContainedWindows() const = 0;
    windowsContainerType getAllContainedWindows() const;
    
    curses::UIcontrol * getNextUIcontrolHavingFocus();
    void setHandle(WINDOW * windowHandle) { //m_windowHandle = windowHandle;
      m_bReference = true;
      m_windowHandle = windowHandle; }
    void SetFocusToNextUIcontrol();
    void showAllContainedWindows();
//    /*curses::UIcontrol*/ Curses::WindowHandleWindow * getUIcontrolHavingFocus() const;
  };
}
