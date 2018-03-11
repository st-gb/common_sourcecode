/** File:   Label.cpp
 * Author: sg
 * Created on 10. März 2018, 20:50 */

#include "Label.hpp"

namespace curses {
Label::Label() {
}

Label::~Label() {
}

void Label::GetMinimalSize(int & width, int & height)
{
  width = m_label.length();
  height = 1;
}

void Label::show()
{
  if(m_windowHandle)
  {
    /**The new label may be a short form of the old label, so erase all before.*/
    wclear(m_windowHandle);
    mvwaddstr(m_windowHandle, 0, 0, m_label.c_str() );
    wrefresh(m_windowHandle);
  }
}

}
