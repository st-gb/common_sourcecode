#include "Menu.hpp" //class Menu
#include <stdlib.h> //malloc(...), free(...)
#include <map>
#include <set> //class std::set
#include <curses.h> //KEY_DOWN

namespace PDcurses
{
  Menu::Menu()
    : m_currentMenuItem(0)
  {    
  }
  
  Menu::~Menu()
  {
  }

  /** Checks if an access key together with name exists more than once */
  int Menu::checkUniqueAcceleratorKey(const char name[])
  {
    std::set<char> acceleratorKeys;
    for(MenuLabelAndFunctionType::const_iterator cIter = 
      m_menuLabelAndFunction.begin(); cIter != m_menuLabelAndFunction.end(); 
      cIter ++)
    {
      const std::string & menuLabel = cIter->m_label;
      const std::string::size_type charIndexOfAmpersand = menuLabel.find('&');
      if( charIndexOfAmpersand != std::string::npos && 
          charIndexOfAmpersand < menuLabel.length() )
      {
        const char acceleratorKey = menuLabel.at(charIndexOfAmpersand);
        if( acceleratorKeys.find(acceleratorKey) == acceleratorKeys.end() )
          return -1;
        acceleratorKeys.insert(acceleratorKey);
      }
    }
    return 0;
  }
  
  int Menu::addMenuItem(const char name[], FUNC func )
  {
    int i = checkUniqueAcceleratorKey(name);
    if( i == 0)
    {
      m_menuLabelAndFunction.push_back( MenuLabelAndFunction() );
    }
  }

//  void Menu::createMenu()
//  {
//    const int numMenuItems = m_menuLabelAndFunction.size();
//  }

  int Menu::HandleAction(int currentAction)
  {
    switch(currentAction)
    {
      case KEY_DOWN:
        m_currentMenuItem ++;
        break;
      case KEY_UP:
        m_currentMenuItem --;
        break;
      case 0xA: /* Return- bzw. Enter-Taste -> ASCII-Code */
        //ret = item_index(current_item(m_menu) );
//        FUNC func = m_functionToCallVector.at(ret);
//        m_menuLabelAndFunction.
//        (*func)();
        break;
      default:
        return Curses::Window::inputNotHandled;
    }
  }

  /** Adapt "void doMenu(menu * pMenu)" from  
   *   PDcurses demo: tui.c  */
  int Menu::InsideMenu(bool ESCandENTERleavesMenu, WINDOW * windowToShowMenuIn)
  {
    int ret = -1;
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
          m_currentMenuItem ++;
          break;
        case KEY_UP:
          m_currentMenuItem --;
          break;
        case 0xA: /* Return- bzw. Enter-Taste -> ASCII-Code */
          FUNC func = m_functionToCallVector.at(ret);
          (*func)();
          if( ESCandENTERleavesMenu )
            stayInMenu = false;
          break;
  //          exit(0);
      }
    }while( stayInMenu );
    wrefresh(windowToShowMenuIn);
    return ret;
  }
}
