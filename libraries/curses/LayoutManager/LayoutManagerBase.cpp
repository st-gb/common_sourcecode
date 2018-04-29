#include "LayoutManagerBase.hpp"
#include "../UIcontrols/UIcontrol.hpp"
#include "libraries/curses/windows/WindowHandleWindow.hpp"

namespace curses
{
  void LayoutManagerBase::destroyAllContainedWindows()
  {
    curses::LayoutManagerBase::windowsContainerType windowVector = 
      getAllContainedWindows();
    Curses::Window * p_cursesWindow;
    curses::WindowHandleWindow * p_cursesWindowHandleWindow;
    for( curses::LayoutManagerBase::windowsContainerType::const_iterator 
      windowIterator = windowVector.begin(); 
      windowIterator != windowVector.end() ; windowIterator ++)
    {
      p_cursesWindow = *windowIterator;
      p_cursesWindowHandleWindow = dynamic_cast<curses::WindowHandleWindow *>
        (p_cursesWindow);
      curses::LayoutManagerBase * p_layoutManager = NULL;
      if(p_cursesWindowHandleWindow)
        p_layoutManager = p_cursesWindowHandleWindow->getLayoutManager();
      if(p_layoutManager)
      {
        /** The layout in a window may be/is a tree structure: layout managers 
         *  may contain other layout managers. So do recursion here */
        p_layoutManager->destroyAllContainedWindows();
        delete p_layoutManager;
      }
      else
        delete p_cursesWindow;
    }
  }
  
  void LayoutManagerBase::showAllContainedWindows()
  {
    curses::LayoutManagerBase::windowsContainerType windowVector = 
      getAllContainedWindows();
    Curses::Window * p_cursesWindow;
    for( curses::LayoutManagerBase::windowsContainerType::const_iterator 
      windowIterator = windowVector.begin(); 
      windowIterator != windowVector.end() ; windowIterator ++)
    {
      p_cursesWindow = *windowIterator;
      curses::UIcontrol * p_uiControl = (curses::UIcontrol *)
        dynamic_cast<const curses::UIcontrol * const >(p_cursesWindow);
      if( p_uiControl )
        p_uiControl->show();
    }
  }
  
  curses::LayoutManagerBase::windowsContainerType LayoutManagerBase::getAllContainedWindows() const {
    curses::LayoutManagerBase::windowsContainerType overallVec;
    curses::LayoutManagerBase::windowsContainerType directlyContainedWindows = 
      getDirectlyContainedWindows();
    overallVec.insert(overallVec.end(), directlyContainedWindows.begin(), directlyContainedWindows.end());
    Curses::Window * p_cursesWindow;
    curses::WindowHandleWindow * p_cursesWindowHandleWindow;
//    m_windowHandle
#ifdef _DEBUG
#endif
    for(curses::LayoutManagerBase::windowsContainerType::const_iterator iter = 
        directlyContainedWindows.begin(); iter != directlyContainedWindows.end() ; iter++ )
    {
      p_cursesWindow = *iter;
      p_cursesWindowHandleWindow = dynamic_cast<curses::WindowHandleWindow *>
        (p_cursesWindow);
      if( p_cursesWindowHandleWindow )
      {
        curses::LayoutManagerBase * p_layoutManager = (curses::LayoutManagerBase *)
          dynamic_cast<const curses::LayoutManagerBase * const >(p_cursesWindowHandleWindow);
        if( ! p_layoutManager )
          p_layoutManager = p_cursesWindowHandleWindow->getLayoutManager();
        /** recursively add all other windows. */
        if( p_layoutManager )
        {
          /** Recursion (calls _this_ function) here.*/
          curses::LayoutManagerBase::windowsContainerType currentVec = 
            p_layoutManager->getAllContainedWindows();
          /** from https://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector */
          overallVec.insert(overallVec.end(), currentVec.begin(), currentVec.end());
        }
      }
    }
    return overallVec;
  }

/*curses::UIcontrol*/ curses::UIcontrol * LayoutManagerBase::getNextUIcontrolHavingFocus()
{
  curses::UIcontrol * p_cursesUIcontrol;
  Curses::Window * p_cursesWindow;
  curses::WindowHandleWindow * p_cursesWindowHandleWindow;
  /** all windows contained in this layout and indirect layout contained (like a tree) */
  curses::LayoutManagerBase::windowsContainerType overallVec = getAllContainedWindows();
  curses::LayoutManagerBase::windowsContainerType::const_iterator iterOfCurrentFocus = overallVec.end();  
  for( curses::LayoutManagerBase::windowsContainerType::const_iterator iter = overallVec.begin(); 
      iter != overallVec.end() ; iter ++)
  {
    p_cursesWindow = *iter;
    p_cursesWindowHandleWindow = dynamic_cast<curses::WindowHandleWindow *>
        (p_cursesWindow);
    if( p_cursesWindowHandleWindow )
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
    for( curses::LayoutManagerBase::windowsContainerType::const_iterator iter = overallVec.begin(); 
        iter != iterOfCurrentFocus ; iter ++)
    {
      p_cursesWindow = *iter;
      if( p_cursesWindow->IsUIcontrol() )
      {
        p_cursesUIcontrol = (curses::UIcontrol *) p_cursesWindow;
        curses::UIcontrol * p_winWithCurrentFocus = (curses::UIcontrol *) 
          *iterOfCurrentFocus;
        p_winWithCurrentFocus->SetFocus(false);
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

