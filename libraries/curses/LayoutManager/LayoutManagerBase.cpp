#include "LayoutManagerBase.hpp"
#include "../UIcontrols/UIcontrol.hpp"
#include "libraries/curses/windows/WindowHandleWindow.hpp"

namespace curses
{
  std::vector<ncurses::WindowHandleWindow *> LayoutManagerBase::getAllContainedWindows() const {
    std::vector<ncurses::WindowHandleWindow *> overallVec;
    std::vector<ncurses::WindowHandleWindow *> directlyContainedWindows = 
      getDirectlyContainedWindows();
    overallVec.insert(overallVec.end(), directlyContainedWindows.begin(), directlyContainedWindows.end());
    ncurses::WindowHandleWindow * p_cursesWindow;
//    m_windowHandle
#ifdef _DEBUG
#endif
    for(std::vector<ncurses::WindowHandleWindow *>::const_iterator iter = 
        directlyContainedWindows.begin(); iter != directlyContainedWindows.end() ; iter++ )
    {
      p_cursesWindow = *iter;
      curses::LayoutManagerBase * p_layoutManager = (curses::LayoutManagerBase *)
        dynamic_cast<const curses::LayoutManagerBase * const >(p_cursesWindow);
      if( ! p_layoutManager )
        p_layoutManager = p_cursesWindow->getLayoutManager();
      /** recursively add all other windows. */
      if( p_layoutManager )
      {
        /** Recursion (calls _this_ function) here.*/
        std::vector<ncurses::WindowHandleWindow *> currentVec = 
          p_layoutManager->getAllContainedWindows();
        /** from https://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector */
        overallVec.insert(overallVec.end(), currentVec.begin(), currentVec.end());
      }
    }
    return overallVec;
  }

/*curses::UIcontrol*/ curses::UIcontrol * LayoutManagerBase::getNextUIcontrolHavingFocus()
{
  curses::UIcontrol * p_cursesUIcontrol;
  ncurses::WindowHandleWindow * p_cursesWindow;
  /** all windows contained in this layout and indirect layout contained (like a tree) */
  std::vector<ncurses::WindowHandleWindow *> overallVec = getAllContainedWindows();
  std::vector<ncurses::WindowHandleWindow *>::const_iterator iterOfCurrentFocus = overallVec.end();  
  for( std::vector<ncurses::WindowHandleWindow *>::const_iterator iter = overallVec.begin(); 
      iter != overallVec.end() ; iter ++)
  {
    p_cursesWindow = *iter;
    if( p_cursesWindow->IsUIcontrol() )
    {
      p_cursesUIcontrol = (curses::UIcontrol *) p_cursesWindow;
      if( iterOfCurrentFocus != overallVec.end() )
      {
        ((curses::UIcontrol *) *iterOfCurrentFocus)->SetFocus(false);        
        return p_cursesUIcontrol;
      }
      else if(p_cursesUIcontrol->HasFocus() )
      {
//        if( iterOfCurrentFocus == overallVec.end() )
          iterOfCurrentFocus = iter;
      }
    }
  }
  /** No UI control found _after_ UI control with focus. */
  if( iterOfCurrentFocus != overallVec.end())
  {
    for( std::vector<ncurses::WindowHandleWindow *>::const_iterator iter = overallVec.begin(); 
        iter != iterOfCurrentFocus ; iter ++)
    {
      p_cursesWindow = *iter;
      if( p_cursesWindow->IsUIcontrol() )
      {
        p_cursesUIcontrol = (curses::UIcontrol *) p_cursesWindow;
        p_cursesUIcontrol->SetFocus(false);
        return p_cursesUIcontrol;
      }
    }
  }
  return NULL;
}

void LayoutManagerBase::SetFocusToNextUIcontrol()
{
  curses::UIcontrol * p_UIcontrol = getNextUIcontrolHavingFocus();
  if( p_UIcontrol )
  {
    p_UIcontrol->SetFocus(true);
  }
}

} /** namespace end */

