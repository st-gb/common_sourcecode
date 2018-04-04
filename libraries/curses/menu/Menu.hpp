#pragma once //include guard

#include <vector> //class std::vector
#include <map> //class std::map
//#include <libraries/ncurses/InputProcessorStack.hpp>
#include <libraries/curses/windows/Window.hpp>
#include <string> //class std::string
//#include "MenuBar.hpp"
#include "MenuLabelAndFunction.hpp"
#include <hardware/CPU/fastest_data_type.h>
#include <libraries/curses/windows/WindowHandleWindow.hpp>

/** Forward declarations (faster than to #include) */
struct _win_st; //WINDOW

namespace curses
{
  class Menu
    : public 
      Curses::Window
      //curses::MenuBar
  {
  public:
    enum style { Vertical, Horizontal};
    std::string m_label;
   private:
    int m_numRowsNeeded, m_numColumnsNeeded;
    bool m_ESCandENTERleavesMenu;
    bool m_stayInMenu;
    enum style m_alignment;
    WINDOW * m_subMenuWindow;
    fastestUnsignedDataType m_currentMenuItemSelection;
    typedef std::vector<curses::MenuLabelAndFunction> MenuItemContainerType;
    MenuItemContainerType m_menuItemContainer;
    curses::WindowHandleWindow * m_win;
   public:
    Menu(curses::WindowHandleWindow * win);//{ }
    //TODO: win = main window (toplevel window that contains subwindows)?!
    Menu(const char * const label/*, chtype colorPair*/, curses::WindowHandleWindow * win ) 
      : m_label(label)/*, m_colorPair(colorPair)*/
        , m_win(win)
      { }
    virtual ~Menu();// {}
    
    virtual int addMenuItem(const char str [], void (*FUNC)(void) = 0 );
    virtual WINDOW * create(WINDOW * windowToShowMenuIn) { return 0; };
    virtual void createMenu(enum style _style = Vertical) {};
    char GetHotKey();
    signed GetHotKeyCharIndex() const;
    void drawMenuItems();
    fastestUnsignedDataType getLargestMenuItemStringLength() const;
    int HandleAction(const int ch);
//    int InsideMenu(bool = true, WINDOW * windowToShowMenuIn = 0 );
    void SetEnterLeavesMenu(bool b){ m_ESCandENTERleavesMenu = b; }
    int GetNumRowsNeeded() const { return m_numRowsNeeded; }
    int GetNumColumnsNeeded() const { return m_numColumnsNeeded; }
    void show(WINDOW * p_windowForRelativePos);
  };
}
