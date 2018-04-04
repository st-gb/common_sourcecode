#pragma once

#include "../windows/WindowHandleWindow.hpp"
#include "Menu.hpp" //base class
#include <map> //class std::map
#include <string> //class std::string

namespace curses { class Menu; }

namespace curses
{
  class MenuBar
    : public curses::WindowHandleWindow
  {
  public:
    typedef std::map<int,curses::Menu> MenuContainerType;
  private:
    MenuContainerType m_menus;
  public:
    struct MenuLabelAndMenu
    {
      std::string m_label;
      curses::Menu * m_menu;
    };
    void addMenu(curses::Menu & menu);
    MenuContainerType GetMenus() const { return m_menus; }
    int HandleAction(const int ch);
    void show();
  };
}
