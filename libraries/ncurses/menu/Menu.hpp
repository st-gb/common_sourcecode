#pragma once //include guard

#include <vector> //class std::vector
#include <map> //class std::map
//#include <libraries/ncurses/InputProcessorStack.hpp>
//#include <libraries/curses/windows/Window.hpp>
#include <libraries/curses/menu/Menu.hpp> //base class

/** Forward declarations (faster than to #include) */
struct tagITEM;
struct tagMENU;
struct _win_st; //WINDOW

namespace ncurses
{
  class Menu
    : public curses::Menu
  {
  public:
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
    WINDOW * m_subMenuWindow;
   public:
    Menu();
    ~Menu();
    
    int addMenuItem(const char str [], void (*FUNC)(void) = 0 );
    WINDOW * create(WINDOW * windowToShowMenuIn);
    void createMenu(enum style _style = Vertical);
    int HandleAction(const int ch);
    int InsideMenu(bool = true, WINDOW * windowToShowMenuIn = 0 );
    void SetEnterLeavesMenu(bool b){ m_ESCandENTERleavesMenu = b; }
    int GetNumRowsNeeded() const { return m_numRowsNeeded; }
    int GetNumColumnsNeeded() const { return m_numColumnsNeeded; }
  };
}
