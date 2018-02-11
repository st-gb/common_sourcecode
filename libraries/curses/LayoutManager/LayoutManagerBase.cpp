#include "LayoutManagerBase.hpp"
#include "../UIcontrols/UIcontrol.hpp"
#include "libraries/curses/windows/WindowHandleWindow.hpp"

namespace curses
{
  std::vector<Curses::WindowHandleWindow *> LayoutManagerBase::getAllContainedWindows() const {
    std::vector<Curses::WindowHandleWindow *> overallVec;
    std::vector<Curses::WindowHandleWindow *> directlyContainedWindows = 
      getDirectlyContainedWindows();
    overallVec.insert(overallVec.end(), directlyContainedWindows.begin(), directlyContainedWindows.end());
    Curses::WindowHandleWindow * p_cursesWindow;
//    m_windowHandle
#ifdef _DEBUG
#endif
    for(std::vector<Curses::WindowHandleWindow *>::const_iterator iter = 
        directlyContainedWindows.begin(); iter != directlyContainedWindows.end() ; iter++ )
    {
      p_cursesWindow = *iter;
      curses::LayoutManagerBase * p_lm = p_cursesWindow->getLayoutManager();
      /** recursively add all other windows. */
      if( p_lm )
      {
        /** Recursion (calls _this_ function) here.*/
        std::vector<Curses::WindowHandleWindow *> currentVec = p_lm->getAllContainedWindows();
        /** from https://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector */
        overallVec.insert(overallVec.end(), currentVec.begin(), currentVec.end());
      }
    }
    return overallVec;
  }

/*curses::UIcontrol*/ curses::UIcontrol * LayoutManagerBase::getNextUIcontrolHavingFocus()
{
  curses::UIcontrol * p_cursesUIcontrol;
  Curses::WindowHandleWindow * p_cursesWindow;
  /** all windows contained in this layout and indirect layout contained (like a tree) */
  std::vector<Curses::WindowHandleWindow *> overallVec = getAllContainedWindows();
  std::vector<Curses::WindowHandleWindow *>::const_iterator iterOfCurrentFocus = overallVec.end();  
  for( std::vector<Curses::WindowHandleWindow *>::const_iterator iter = overallVec.begin(); 
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
    for( std::vector<Curses::WindowHandleWindow *>::const_iterator iter = overallVec.begin(); 
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

