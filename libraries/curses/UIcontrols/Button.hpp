/** File:   Button.hpp
 * Author: sg
 * Created on 9. März 2018, 10:34  */

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../windows/WindowHandleWindow.hpp"

namespace curses {
class Button
  : public ncurses::WindowHandleWindow
{
  std::string m_label;
public:
  Button();
  Button(const char * const label);
  virtual ~Button();
  
//  void create(WINDOW * win);
  void GetMinimalSize(int & width, int & height);
  void show();
private:

};
}

#endif /* BUTTON_HPP */

