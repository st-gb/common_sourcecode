/** File:   Button.cpp
 * Author: sg
 * Created on 9. März 2018, 10:34  */

#include <string>

#include "Button.hpp"

namespace curses {
Button::Button() {
}

Button::Button(const char * const label) {
  m_label = label;
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

void Button::show()
{
  if(m_windowHandle)
  {
    mvwaddstr(m_windowHandle, 0, 0, m_label.c_str() );
    wrefresh(m_windowHandle);
  }
}
}/** end namespace */
