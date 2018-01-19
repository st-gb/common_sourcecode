#pragma once //include guard

#include <vector> //class std::vector
#include <map> //class std::map
//#include <libraries/ncurses/InputProcessorStack.hpp>
#include <libraries/curses/Window.hpp>

/** Forward declarations (faster than to #include) */
struct tagITEM;
struct tagMENU;
struct _win_st; //WINDOW

namespace Curses
{
  class Menu
    : public Window
  {
  public:
    enum style { Vertical, Horizontal};
    typedef void (*FUNC)(void);
   private:
    int m_numRowsNeeded, m_numColumnsNeeded;
    bool m_ESCandENTERleavesMenu;
    bool m_stayInMenu;
    enum style m_alignment;
    tagITEM ** m_menuItems;
    tagMENU * m_menu;
    std::vector<tagITEM *> m_menuItemVector;
    std::vector<FUNC> m_functionToCallVector;
    std::map<tagITEM *, FUNC> m_menuItemMap;
   public:
    Menu();
    ~Menu();
    
    void addMenuItem(const char str [], void (*FUNC)(void) = 0 );
    void createMenu(enum style _style = Vertical);
    int HandleAction(const int ch);
    int InsideMenu(bool = true, struct _win_st * windowToShowMenuIn = 0 );
    void SetEnterLeavesMenu(bool b){ m_ESCandENTERleavesMenu = b; }
    int GetNumRowsNeeded() const { return m_numRowsNeeded; }
    int GetNumColumnsNeeded() const { return m_numColumnsNeeded; }
  };
}
