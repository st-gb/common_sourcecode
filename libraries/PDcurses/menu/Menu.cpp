#include "Menu.hpp" //class Menu
#include <stdlib.h>
#include <map> //malloc(...), free(...)

namespace PDcurses
{
  Menu::Menu()
    : m_menu(NULL)
  {
    
  }
  
  Menu::~Menu()
  {
    if( m_menu )
    {
      /** from https://de.wikibooks.org/wiki/Ncurses:_Men%C3%BCs */
      const int numMenuItems = m_menuItemVector.size();
      for(int menuItemIndex = 0; menuItemIndex < numMenuItems ; menuItemIndex++)
      {
        
      }
    }
  }

  void Menu::addMenuItem(const char str [], FUNC func )
  {
    ITEM * menuItem = new_item(str, "");
    m_menuItemVector.push_back(menuItem);
    m_functionToCallVector.push_back(func);
    m_menuItemMap.insert(std::make_pair(menuItem, func) );
  }

  void Menu::createMenu()
  {
    const int numMenuItems = m_menuItemVector.size();
    m_menuItems = (ITEM **) calloc( numMenuItems + 1, sizeof(ITEM *));
    for(int menuItemIndex = 0; menuItemIndex < numMenuItems ; menuItemIndex++)
    {
      m_menuItems[menuItemIndex] = m_menuItemVector.at(menuItemIndex);
    }
    m_menuItems[numMenuItems] = 0; //end marker
    
    m_menu = new_menu(m_menuItems);
  }

  /** Adapt "void doMenu(menu * pMenu)" from  
   *   PDcurses demo: tui.c  */
  int Menu::InsideMenu(bool ESCandENTERleavesMenu, WINDOW * windowToShowMenuIn)
  {
    int ret = -1;
    /** from https://de.wikibooks.org/wiki/Ncurses:_Men%C3%BCs */
    if( windowToShowMenuIn ) {
      set_menu_win (m_menu, windowToShowMenuIn);
      set_menu_sub (m_menu, derwin(windowToShowMenuIn, 4 /*# lines*/, 
        28 /* # columns */, 0 /*  begin_y */, 0 /*  begin_x */ ) );
    }
    post_menu(m_menu);
    int ch;
    bool stayInMenu = true;
    do
    {
      ch = getch();
      if( ch != -1 )
        //mvaddstr(7, 3, "d" );
        mvprintw(7, 3, "%d %c", ch, ch );
      switch(ch)
      {
        case 27:
          if( ESCandENTERleavesMenu )
            stayInMenu = false;
          break;
        case KEY_DOWN:
          menu_driver(m_menu, REQ_DOWN_ITEM);
          break;
        case KEY_UP:
          menu_driver(m_menu, REQ_UP_ITEM);
          break;
        case 0xA: /* Return- bzw. Enter-Taste -> ASCII-Code */
          ret = item_index(current_item(m_menu) );
          FUNC func = m_functionToCallVector.at(ret);
          (*func)();
          if( ESCandENTERleavesMenu )
            stayInMenu = false;
          break;
  //          exit(0);
      }
    }while( stayInMenu );
    unpost_menu(m_menu);
    wrefresh(windowToShowMenuIn);
    return ret;
  }
}

