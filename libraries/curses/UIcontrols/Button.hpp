/** File:   Button.hpp
 * Author: sg
 * Created on 9. März 2018, 10:34  */

#ifndef BUTTON_HPP
#define BUTTON_HPP

//#include "../windows/WindowHandleWindow.hpp"
#include "UIcontrol.hpp"

namespace curses {
class Button
  : public //ncurses::WindowHandleWindow
    curses::UIcontrol
{
  std::string m_label;
public:
  Button();
  Button(const char * const label);
  virtual ~Button();
  
//  void create(WINDOW * win);
  void GetMinimalSize(int & width, int & height);
  void SetColor(chtype color) {}
  void SetLabel(const char * const label) {
    m_label = label;
  }
  void show();
private:

};
}

#endif /* BUTTON_HPP */

