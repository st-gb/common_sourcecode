/** File:   Button.cpp
 * Author: sg
 * Created on 9. März 2018, 10:34  */

#include <string>

#include "Button.hpp"
#include "../color.h" //setcolor(...)

namespace curses {
Button::Button() {
}

Button::~Button() {
}

//void Button::create(WINDOW * win)
//{
////  win = newwin()
//}

void Button::GetMinimalSize(int & width, int & height)
{
  width = m_label.length();
  height = 1;
}

int Button::HandleAction(const int ch)
{
  switch (ch)
  {
    case 0xA:
      return 0xA;
      break;
  }
  return Curses::Window::inputNotHandled;
}
  
void Button::show()
{
  if(m_windowHandle)
  {
    setcolor(m_windowHandle, m_colorPair);
    mvwaddstr(m_windowHandle, 0, 0, m_label.c_str() );
    wrefresh(m_windowHandle);
  }
}

}/** end namespace */
