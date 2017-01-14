#include "InputProcessorStack.hpp"
#include "menu/Menu.hpp"

namespace Ncurses
{
  void InputProcessorStack::consume(const int ch) {
    container_type::const_reverse_iterator iter = m_inputProcessorStack.rbegin();
    if( iter != m_inputProcessorStack.rend() )
    {
      /** Start with the second from last element. */
      iter ++;
      /** Traverse the container from last element added in direction to the 
      *  first added element. */
      for( ; iter != m_inputProcessorStack.rend() ; iter++ )
      {
        Ncurses::Window * p_win = *iter;
        /** If event was consumed by window. */
        if( p_win->HandleAction(ch) > Ncurses::Window::inputNotHandled )
          break;
      }
    }
  }
}
