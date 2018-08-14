#include "Menu.hpp"
#include "../EventQueue.hpp"
#include "ncurses/MainWindow.hpp"
#include "../color.h"

#ifndef NCURSES_CONST
  #define NCURSES_CONST const
#endif

extern curses::EventQueue g_eventQueue;

namespace curses
{
  Menu::Menu(curses::WindowHandleWindow * win)
    : m_currentMenuItemSelection(0),
      m_win(win)
  {
    
  }

  Menu::~Menu()
  {
  }
  
  int Menu::addMenuItem(const char str [], FUNC f )
  {
    curses::MenuLabelAndFunction menuItemLabelAndFunction = {str, f};
    m_menuItemContainer.push_back(menuItemLabelAndFunction);
  }
    
  signed Menu::GetHotKeyCharIndex() const
  {
    const int charIndexOfAmpersAnd = m_label.find('&');
    if( charIndexOfAmpersAnd != std::string::npos )
    {
      if(m_label.length() > charIndexOfAmpersAnd  + 1)
        return charIndexOfAmpersAnd  + 1;
    }
    return std::string::npos;
  }

  char Menu::GetHotKey()
  {
    signed s = GetHotKeyCharIndex();
    if( s > -1 )
      return m_label[s];
    return 0;
  }

  void Menu::drawMenuItems()
  {
    signed index = 0;
    colorBox(m_subMenuWindow, BODY_WINDOW_COLOR, 0);
    for(MenuItemContainerType::const_iterator iter = m_menuItemContainer.begin(); 
        iter != m_menuItemContainer.end(); iter ++, index ++)
    {
      if( m_currentMenuItemSelection == index )
//        color_set(BODY_WINDOW_COLOR, BUTTON_COLOR);
//        attron(COLOR_PAIR(1));
        setcolor(m_subMenuWindow, BUTTON_COLOR);
      mvwprintw(m_subMenuWindow, 
        index, 
        0, "%s", iter->m_label.c_str() );
      if( m_currentMenuItemSelection == index )
//        color_set(BLACK_ON_GREEN, GREEN_ON_BLACK);
//        attron(COLOR_PAIR(2));
        setcolor(m_subMenuWindow, BODY_WINDOW_COLOR);
    }
    touchwin(m_subMenuWindow);
    wrefresh(stdscr);
    wrefresh(m_subMenuWindow);
  }
  
  fastestUnsignedDataType Menu::getLargestMenuItemStringLength() const
  {
    fastestUnsignedDataType largestMenuItemStringLength = 0;    
    for(MenuItemContainerType::const_iterator iter = m_menuItemContainer.begin(); 
        iter != m_menuItemContainer.end(); iter ++)
    {
      const std::string & label = iter->m_label;
      if( label.length() > largestMenuItemStringLength)
        largestMenuItemStringLength = label.length();
    }
    return largestMenuItemStringLength;
  }
  
  void Menu::show(WINDOW * p_windowForRelativePos)
  {
    unsigned largestMenuItemStringLength = getLargestMenuItemStringLength();
    m_subMenuWindow = Curses::Window::CreateWindowRelativePos(
      p_windowForRelativePos
      , m_menuItemContainer.size()
      , largestMenuItemStringLength
      , 1, 0
      );
    drawMenuItems();
  }

  int Menu::HandleAction(const int ch)
  {
//      if( ch != ERR )
//        mvprintw(7, 3, "%d %c", ch, ch );
    int ret = ch;
    bool consumedInput = true;
    /** see https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses */
    NCURSES_CONST char * keyName = keyname(ch);
    switch(ch)
    {
      case KEY_RESIZE :
        ret = inputNotHandled;
        break;
      case 27:
//        if( m_ESCandENTERleavesMenu )
//          m_stayInMenu = false;
        s_inputProcessorStack.RemoveLastElement();
        m_win->UpdateAffectedWindows(m_subMenuWindow);
//        touchwin(m_subMenuWindow);
//        wrefresh(m_subMenuWindow);
//        touchwin(stdscr);
//        wrefresh(stdscr);
//        ret = ch;
        break;
      case KEY_DOWN:
        if( m_alignment == Vertical )
        {
          if( m_currentMenuItemSelection + 1 < m_menuItemContainer.size() )
          {
            m_currentMenuItemSelection ++;
            drawMenuItems();
          }
//          ret = ch;
        }
//        else
//          ret = Curses::Window::inputNotHandled;
        break;
      case KEY_UP:
        if( m_alignment == Vertical )
        {
          if( m_currentMenuItemSelection > 0 )
          {
            m_currentMenuItemSelection --;
            drawMenuItems();
          }
        }
//        ret = ch;
//        else
//          ret = Curses::Window::inputNotHandled;
        break;
      /** For horizontal menus: */
      case KEY_RIGHT:
        if( m_alignment == Horizontal )
        {
          if( m_currentMenuItemSelection < m_menuItemContainer.size() )
            m_currentMenuItemSelection ++;
        }
//        else
//          ret = Curses::Window::inputNotHandled;         
        break;
      case KEY_LEFT:
        if( m_alignment == Horizontal )
        {
          if( m_currentMenuItemSelection > 0 )
            m_currentMenuItemSelection --;
        }
//        else
//          ret = Curses::Window::inputNotHandled;         
        break;
      case 0xA: /* Return- bzw. Enter-Taste -> ASCII-Code */
      {
        FUNC func = m_menuItemContainer.at(m_currentMenuItemSelection).m_function;
//        (*func)();
        //TODO add fuction to call?!
        g_eventQueue.addEvent(func);
        s_inputProcessorStack.RemoveLastElement();
        m_win->UpdateAffectedWindows(m_subMenuWindow);
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
//        ret = Curses::Window::inputNotHandled;
    }
//    if( consumedInput )
//      wrefresh(windowToShowMenuIn);
    return ret;
  }

  //WINDOW * create(WINDOW * windowToShowMenuIn);
}

