
#pragma message "link with \"menu\" (ncurses menu library) in order for this to work"

/** ncurses menu functions and structs: unpost_menu(...), free_menu(...) */
#include <menu.h> 
#include "Menu.hpp" //C++ ncurses menu wrapper
#include <libraries/curses/EventQueue.hpp>
#include <stdlib.h> //malloc(...), free(...)
#include <map> //class std::map
#include <libraries/curses/GetChar.hpp> // int GetChar(WINDOW * p_window);
#include "OperatingSystem/multithread/GetCurrentThreadNumber.hpp"
#include <libraries/curses/windows/WindowHandleWindow.hpp>
//#include <eti.h> //E_OK

/** static/class variable definitons : */
//extern Curses::InputProcessorStack Curses::Window::s_inputProcessorStack;
extern ncurses::EventQueue g_eventQueue;

namespace ncurses
{
  Menu::Menu(ncurses::WindowHandleWindow * win)
    : curses::Menu(win),
      m_ESCandENTERleavesMenu(true), 
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

  /** @param func: function to execute when menu item is selected */
  int Menu::addMenuItem(const char str [], FUNC func )
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
    int n = scale_menu(m_menu, & m_numRowsNeeded, & m_numColumnsNeeded);
  }

//  std::vector<tagITEM *> & Menu::GetMenuItemVector()
//  {
//    return m_menuItemVector;
//  }
  
  int Menu::HandleAction(const int ch)
  {
//      if( ch != ERR )
//        mvprintw(7, 3, "%d %c", ch, ch );
    int ret = -2;
    bool consumedInput = true;
    /** see https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses */
    NCURSES_CONST char * keyName = keyname(ch);
    switch(ch)
    {
      case 27:
        if( m_ESCandENTERleavesMenu )
          m_stayInMenu = false;
        break;
      case KEY_DOWN:
        if( m_alignment == Vertical )
        {
          /** https://linux.die.net/man/3/menu_driver : */
          int menu_driverReturnCode = menu_driver(m_menu, REQ_DOWN_ITEM);
#ifdef _DEBUG
//          menu_driverReturnCode += 0;
          switch(menu_driverReturnCode)
          {
            case E_OK :
              break;
          }
//          int i = menu_driverReturnCode;
#endif //_DEBUG
        }
        else
          ret = Curses::Window::inputNotHandled;
        break;
      case KEY_UP:
        if( m_alignment == Vertical )
          menu_driver(m_menu, REQ_UP_ITEM);
        else
          ret = Curses::Window::inputNotHandled;
        break;
      /** For horizontal menus: */
      case KEY_RIGHT:
        if( m_alignment == Horizontal )
          menu_driver(m_menu, REQ_RIGHT_ITEM);
        else
          ret = Curses::Window::inputNotHandled;         
        break;
      case KEY_LEFT:
        if( m_alignment == Horizontal )
          menu_driver(m_menu, REQ_LEFT_ITEM);
        else
          ret = Curses::Window::inputNotHandled;         
        break;
      case 0xA: /* Return- bzw. Enter-Taste -> ASCII-Code */
      {
        ITEM * currentMenuItem = current_item(m_menu);
        /** https://linux.die.net/man/3/item_index : "The function item_index 
         *  returns the (zero-origin) index of item in the menu's item pointer list." */
        ret = item_index(currentMenuItem);
        FUNC func = m_functionToCallVector.at(ret);
//        (*func)();
        //TODO add fuction to call?!
        g_eventQueue.addEvent(func);
        if( m_ESCandENTERleavesMenu )
          m_stayInMenu = false;
      }
        break;
      default:
        consumedInput = false;
//        if( keyName[0] == '^') /** Ctrl + key pressed */
//        {
//          otherKey = keyName + 1;
//        }
        ret = Curses::Window::inputNotHandled;
    }
//    if( consumedInput )
//      wrefresh(windowToShowMenuIn);
    return ret;
  }

  WINDOW * Menu::create(WINDOW * windowToShowMenuIn)
  {
    if( ! windowToShowMenuIn )
      windowToShowMenuIn = stdscr;
//    WINDOW * submenuWin = NULL;
    /** from https://de.wikibooks.org/wiki/Ncurses:_Men%C3%BCs */
    if( windowToShowMenuIn ) {      
//      int n = scale_menu(m_menu, & numRowsNeeded, & numColumnsNeeded);
      //TODO does the window return by "derwin(...)" need to be freed?
      m_subMenuWindow = //derwin(windowToShowMenuIn, 
      /** If window was created with derwin(...) or subwin(...) it isn't cleared 
       *  from screen after wdelete(...). So use newwin(...) instead. */
        //newwin(
        Curses::Window::CreateWindowRelativePos(
        windowToShowMenuIn,
        m_numRowsNeeded /*# lines*/, 
        m_numColumnsNeeded /* # columns */, 
        0 /*  begin_y relative to the standard screen (whole terminal) */, 
        0 /*  begin_x  relative to the standard screen (whole terminal)*/ );
//      set_menu_sub (m_menu, submenuWin );
      set_menu_win (m_menu, /*windowToShowMenuIn*/ m_subMenuWindow);
    }
    /** https://linux.die.net/man/3/post_menu : 
     *  "The function post_menu displays a menu to its associated subwindow."*/
    post_menu(m_menu);
    //refresh();
    wrefresh(m_subMenuWindow);
    return m_subMenuWindow;
  }
  
  int Menu::InsideMenu(bool ESCandENTERleavesMenu, WINDOW * windowToShowMenuIn)
  {
    m_ESCandENTERleavesMenu = ESCandENTERleavesMenu;
#ifdef _DEBUG
    int n = OperatingSystem::GetCurrentThreadNumber();
#endif
    WINDOW * submenuWin = create(windowToShowMenuIn);
    m_stayInMenu = true;
    int ret = -1;
    s_inputProcessorStack.add(this);
    
//    if( windowToShowMenuIn ) 
//      wrefresh(windowToShowMenuIn);
    int ch;
    keypad(windowToShowMenuIn, TRUE);   /* enable cursor keys */
    do
    {
      ch = ncurses::GetChar(windowToShowMenuIn);
      /** https://linux.die.net/man/3/wgetch :
       * "In no-delay mode, if no input is waiting, the value ERR is returned."
       * ERR = no valid input. */
      if( ch != ERR )
      {
        ret = HandleAction(ch);
        /** If not consumed (away) by the handler of this object. */
        if( ret == Curses::Window::inputNotHandled )
  //      else
          s_inputProcessorStack.consume(ch);
        /** Without refreshing the menu window a changed menu item entry 
         *  selection doesn't become visible. */
        wrefresh(m_subMenuWindow /*windowToShowMenuIn*/);
//        if(ch == )
      }
    }while( m_stayInMenu );
    unpost_menu(m_menu);
    s_inputProcessorStack.RemoveLastElement();
    if( m_subMenuWindow )
    {
//      wrefresh(submenuWin);
      delwin(m_subMenuWindow);
    }
    /** https://linux.die.net/man/3/touchwin :
        "throw away all optimization information about which parts of the 
     *  window have been touched, by pretending that the entire window has been
     *  drawn on." */
//    touchwin(windowToShowMenuIn);
    
    /** This finally hides menu items from a curses window.
     * https://linux.die.net/man/3/wrefresh :
     *  "The routine wrefresh copies the named window to the physical terminal 
     * screen, taking into account what is already there to do optimizations."*/
    wrefresh(windowToShowMenuIn);
//    wrefresh(/*submenuWin*/ windowToShowMenuIn);
    return ret;
  }
}
