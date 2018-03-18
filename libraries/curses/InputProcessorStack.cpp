#include "InputProcessorStack.hpp"
//#include "menu/Menu.hpp"
#include "windows/Window.hpp" //class Window
#include "UIcontrols/UIcontrol.hpp"

namespace ncurses
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
          delete p_cursesWindow;
          /** Erase last element. */
          m_inputProcessorStack.erase(m_inputProcessorStack.end() --);
          //TODO update window (hide it visually) programmatically
          break;
        }
      }
    }
  }
}
