#include "InputProcessorStack.hpp"
//#include "menu/Menu.hpp"
#include "windows/Window.hpp" //class Window
#include "UIcontrols/UIcontrol.hpp"

namespace curses
{
  void InputProcessorStack::consume(const int ch) {
    container_type::const_reverse_iterator iter = m_inputProcessorStack.rbegin();
    if( iter != m_inputProcessorStack.rend() )
    {
//      /** Start with the second from last element. */
//        iter ++;
      /** Traverse the container from last element added in direction to the 
      *  first added element. */
      for( ; iter != m_inputProcessorStack.rend() ; iter++ )
      {
        Curses::Window * p_cursesWindow = *iter;
#ifdef _DEBUG
        if( p_cursesWindow->IsUIcontrol() )
        {
          curses::UIcontrol * p_uic = (curses::UIcontrol *) p_cursesWindow;
          WINDOW * w = p_uic->getWindowHandle();
        }
#endif
        const int handleActionResult = p_cursesWindow->HandleAction(ch);
        /** If event was consumed by window. */
        if( handleActionResult > Curses::Window::inputNotHandled )
          break;
        else if( handleActionResult == Curses::Window::destroyWindow)
        {
          /** update window (hide it visually) programmatically */
          curses::WindowHandleWindow * p_windowHandleWindow = 
            (curses::WindowHandleWindow *)
            dynamic_cast<const curses::WindowHandleWindow * const >(p_cursesWindow);
          if(p_windowHandleWindow)
            UpdateAllWindowsHiddenBy(p_windowHandleWindow);
          Remove(p_cursesWindow);
          delete p_cursesWindow;
//          /** Erase last element. */
//          m_inputProcessorStack.erase(m_inputProcessorStack.end() --);
          break;
        }
      }
    }
  }
  
  void InputProcessorStack::Remove(Curses::Window * win)
  {
    /** Although it is more likely for the window to be at the end we must use 
      * a forward iterator here because erase() only accepts forward iterators.*/
    for(container_type::iterator iter = 
      m_inputProcessorStack.begin(); iter != m_inputProcessorStack.end(); iter ++ )
    {
      if(*iter == win)
      {
        m_inputProcessorStack.erase(iter);
        break;
      }
    }
  }
  
  
  void InputProcessorStack::RemoveAndDeleteAll()
  {
    for(container_type::iterator iter = 
      m_inputProcessorStack.begin(); iter != m_inputProcessorStack.end(); iter ++ )
    {
      Curses::Window * p_cursesWindow = *iter;
      delete p_cursesWindow;
    }
    m_inputProcessorStack.clear();
    exit = true;
  }
  
  void InputProcessorStack::UpdateAllWindowsHiddenBy(
    const curses::WindowHandleWindow * p_cursesWindowHandleWindow)
  {
    container_type::const_iterator iter = m_inputProcessorStack.begin();
    if( iter != m_inputProcessorStack.end() )
      for( ; iter != m_inputProcessorStack.end() ; iter++ )
      {
        if( *iter != p_cursesWindowHandleWindow )
        {
          curses::WindowHandleWindow * p_windowHandleWindow = 
            (curses::WindowHandleWindow *)
            dynamic_cast<const curses::WindowHandleWindow * const >(*iter);
          if( p_windowHandleWindow)
            p_windowHandleWindow->UpdateAffectedWindows(p_cursesWindowHandleWindow->getWindowHandle());
        }
      }
  }
}
