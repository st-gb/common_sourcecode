#include <algorithm>
#include "MenuBar.hpp"
#include <libraries/curses/curs_set_constants.h>

namespace curses
{
  
  void MenuBar::addMenu(curses::Menu & menu)
  {
    m_menus.insert(std::make_pair(0,menu) );
  }

  void MenuBar::show()
  {
    int x = 0;
    for(MenuContainerType::const_iterator cIter = m_menus.begin(); cIter != 
      m_menus.end() ; cIter ++)
    {
      const std::string & label = cIter->second.m_label;
      const int charIndexOfAmpersAnd = label.find('&');
      if( charIndexOfAmpersAnd != std::string::npos )
      {
        const std::string beforeAmpersAnd = label.substr(0, charIndexOfAmpersAnd);
        mvwaddstr(m_windowHandle, 0 /*y*/, x, beforeAmpersAnd.c_str() );
        x += charIndexOfAmpersAnd;
        //https://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/attrib.html

        attron(A_UNDERLINE);
  //      attrset(A_UNDERLINE);
        const std::string std_strCharToUnderLine = label.substr(charIndexOfAmpersAnd + 1, 
          charIndexOfAmpersAnd + 1);
        mvwaddnstr(m_windowHandle, 0 /*y*/, x, 
          std_strCharToUnderLine.c_str(), 1);
        const chtype charToUnderLine = label.c_str() [charIndexOfAmpersAnd + 1];
//        mvwaddch(m_windowHandle, 0 /*y*/, x, charToUnderLine );
  //      mvwaddnstr(m_windowHandle, 0 /*y*/, x, "%s", 
  //        label.c_str() + charIndexOfAmpersAnd);
        attroff(A_UNDERLINE);
        x += 1;
        const char * afterUnderlinedChar = label.c_str() + charIndexOfAmpersAnd + 2;
        mvwaddstr(m_windowHandle, 0 /*y*/, x, afterUnderlinedChar );
        x += label.length() - charIndexOfAmpersAnd - 1;
      }
      else
        mvwaddstr(m_windowHandle, 0 /*y*/, x, label.c_str() );        
    }
    wrefresh(m_windowHandle);
    s_inputProcessorStack.add(this);
  }

  int MenuBar::HandleAction(const int ch)
  {
    /** see https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses */
    /*NCURSES_CONST*/ const char * keyName = keyname(ch);
    int ret = Curses::Window::inputNotHandled;
    if( keyName[0] == '^') /** Ctrl + key pressed */
    {
      const char * otherKey = keyName + 1;
//          std::vector<tagITEM *> & menuItemVector = s_mainMenu.GetMenuItemVector();
//      const curses::MenuBar::MenuLabelAndMenu & 
      const curses::MenuBar::MenuContainerType & 
        menuLabelAndFunctionContainer = /*s_mainMenu.GetMenuLabelAndFunctionVector()*/
        m_menus;
//          for( std::vector<tagITEM *>::const_iterator cIter = 
//            menuItemVector.begin(); cIter != menuItemVector.end(); cIter++ )
      for(curses::MenuBar::MenuContainerType::iterator cIter = 
          m_menus.begin(); cIter != 
          m_menus.end() ; cIter++ )
      {
//            struct tagITEM * p_menuItem = *cIter;
        curses::Menu & menu = cIter->second;
//            if( otherKey[0] == p_menuItem->name.str[0] )
        if( otherKey[0] == menu.m_label[0] )
        {
          
          /** Hide cursor that may exist from a UI control like a text box
           *  and would be viewed at the position of the menu. */
          const int curs_setResult = curs_set(ncurses::Cursor::Invisible);
//              s_mainMenu.HandleAction('\n');
          menu.HandleAction(otherKey[0]);
          if( curs_setResult != ERR)
            /** Set to previous cursor mode. */
            curs_set(curs_setResult);
          //TODO cursor pos should be like before opening menu.
        }
      }
    }
  }
}
