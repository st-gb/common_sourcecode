
#pragma message "link with \"menu\" (ncurses menu library) in order for this to work"

/** ncurses menu functions and structs: unpost_menu(...), free_menu(...) */
#include <menu.h> 
#include "Menu.hpp" //C++ ncurses menu wrapper
#include <stdlib.h> //malloc(...), free(...)
#include <map> //class std::map
#include <libraries/curses/GetChar.hpp> // int GetChar(WINDOW * p_window);

/** static/class variable definitons : */
Ncurses::InputProcessorStack Ncurses::Window::s_inputProcessorStack;

namespace Ncurses
{
  Menu::Menu()
    : m_ESCandENTERleavesMenu(true), 
      m_stayInMenu(true), 
      m_alignment(Vertical),
      m_menu(NULL)
  {
  
  }
  
  Menu::~Menu()
  {
    if( m_menu )
    {
      /** from https://de.wikibooks.org/wiki/Ncurses:_Men%C3%BCs */
      unpost_menu(m_menu);
      free_menu(m_menu);

      const int numMenuItems = m_menuItemVector.size();
      for(int menuItemIndex = 0; menuItemIndex < numMenuItems ; menuItemIndex++)
      {
        free_item(m_menuItems[menuItemIndex]);
      }
      free(m_menuItems);
    }
  }

  void Menu::addMenuItem(const char str [], FUNC func )
  {
    ITEM * menuItem = new_item(str, "");
    m_menuItemVector.push_back(menuItem);
    m_functionToCallVector.push_back(func);
    m_menuItemMap.insert(std::make_pair(menuItem, func) );
  }

  void Menu::createMenu(enum style _style)
  {
    m_alignment = _style;
    const int numMenuItems = m_menuItemVector.size();
    m_menuItems = (ITEM **) calloc(numMenuItems + /* end marker*/ 1 , 
      sizeof(ITEM *) );
    for(int menuItemIndex = 0; menuItemIndex < numMenuItems ; menuItemIndex++)
    {
      m_menuItems[menuItemIndex] = m_menuItemVector.at(menuItemIndex);
    }
    m_menuItems[numMenuItems] = 0; //end marker
    
    m_menu = new_menu(m_menuItems);
    if( _style == Horizontal )
    {
      //see https://de.wikibooks.org/wiki/Ncurses:_Men%C3%BCs
      set_menu_format(m_menu, 1, numMenuItems /* int cols*/ );
    }
  }

  int Menu::HandleAction(const int ch)
  {
//      if( ch != ERR )
//        mvprintw(7, 3, "%d %c", ch, ch );
    int ret = -2;
    bool consumedInput = true;
    switch(ch)
    {
      case 27:
        if( m_ESCandENTERleavesMenu )
          m_stayInMenu = false;
        break;
      case KEY_DOWN:
        if( m_alignment == Vertical )
          menu_driver(m_menu, REQ_DOWN_ITEM);
        else
          ret = Ncurses::Window::inputNotHandled;
        break;
      case KEY_UP:
        if( m_alignment == Vertical )
          menu_driver(m_menu, REQ_UP_ITEM);
        else
          ret = Ncurses::Window::inputNotHandled;
        break;
      /** For horizontal menus: */
      case KEY_RIGHT:
        if( m_alignment == Horizontal )
          menu_driver(m_menu, REQ_RIGHT_ITEM);
        else
          ret = Ncurses::Window::inputNotHandled;         
        break;
      case KEY_LEFT:
        if( m_alignment == Horizontal )
          menu_driver(m_menu, REQ_LEFT_ITEM);
        else
          ret = Ncurses::Window::inputNotHandled;         
        break;
      case 0xA: /* Return- bzw. Enter-Taste -> ASCII-Code */
      {
        ret = item_index(current_item(m_menu) );
        FUNC func = m_functionToCallVector.at(ret);
        (*func)();
        if( m_ESCandENTERleavesMenu )
          m_stayInMenu = false;
      }
        break;
      default:
        consumedInput = false;
        ret = Ncurses::Window::inputNotHandled;
    }
//    if( consumedInput )
//      wrefresh(windowToShowMenuIn);
    return ret;
  }

  int Menu::InsideMenu(bool ESCandENTERleavesMenu, WINDOW * windowToShowMenuIn)
  {
    m_stayInMenu = true;
    m_ESCandENTERleavesMenu = ESCandENTERleavesMenu;
    int ret = -1;
    s_inputProcessorStack.add(this);
    
    if( ! windowToShowMenuIn )
      windowToShowMenuIn = stdscr;
    WINDOW * submenuWin = NULL;
    /** from https://de.wikibooks.org/wiki/Ncurses:_Men%C3%BCs */
    if( windowToShowMenuIn ) {
      
      int numRowsNeeded, numColumnsNeeded;
      int n = scale_menu(m_menu, & numRowsNeeded, & numColumnsNeeded);
      //TODO does the window return by "derwin(...)" need to be freed?
      submenuWin = //derwin(windowToShowMenuIn, 
      /** If window was created with derwin(...) or subwin(...) it isn't cleared 
       *  from screen after wdelete(...). So use newwin(...) instead. */
        //newwin(
        Ncurses::Window::CreateWindowRelativePos(
        windowToShowMenuIn,
        numRowsNeeded /*# lines*/, 
        numColumnsNeeded /* # columns */, 
        0 /*  begin_y relative to the standard screen (whole terminal) */, 
        0 /*  begin_x  relative to the standard screen (whole terminal)*/ );
//      set_menu_sub (m_menu, submenuWin );
      set_menu_win (m_menu, /*windowToShowMenuIn*/ submenuWin);
    }
    post_menu(m_menu);
    //refresh();
    wrefresh(submenuWin);
//    if( windowToShowMenuIn ) 
//      wrefresh(windowToShowMenuIn);
    int ch;
    keypad(windowToShowMenuIn, TRUE);   /* enable cursor keys */
    do
    {
      ch = Curses::GetChar(windowToShowMenuIn);
      /** https://linux.die.net/man/3/wgetch :
       * "In no-delay mode, if no input is waiting, the value ERR is returned."
       * ERR = no valid input. */
      if( ch != ERR )
      {
        ret = HandleAction(ch);
        /** If not consumed (away) by the handler of this object. */
        if( ret == Ncurses::Window::inputNotHandled )
  //      else
          s_inputProcessorStack.consume(ch);
        wrefresh(/*windowToShowMenuIn*/ submenuWin);
//        if(ch == )
      }
    }while( m_stayInMenu );
    unpost_menu(m_menu);
    s_inputProcessorStack.RemoveLastElement();
    if( submenuWin )
    {
      delwin( submenuWin);
    }
    touchwin(windowToShowMenuIn);
    wrefresh(windowToShowMenuIn);
//    wrefresh(/*windowToShowMenuIn*/ submenuWin);
    return ret;
  }
}
