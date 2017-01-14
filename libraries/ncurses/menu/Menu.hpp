#pragma once //include guard

#include <vector> //class std::vector
#include <map> //class std::map
//#include <libraries/ncurses/InputProcessorStack.hpp>
#include <libraries/ncurses/Window.hpp>

/** Forward declarations (faster than to #include) */
struct tagITEM;
struct tagMENU;
struct _win_st; //WINDOW

namespace Ncurses
{
  class Menu
    : public Window
  {
   public:
    Menu();
    ~Menu();
    
    enum style { Vertical, Horizontal};
    
    void addMenuItem(const char str [], void (*FUNC)(void) = 0 );
    void createMenu(enum style _style = Vertical);
    int HandleAction(const int ch);
    int InsideMenu(bool = true, struct _win_st * windowToShowMenuIn = 0 );
    void SetEnterLeavesMenu(bool b){ m_ESCandENTERleavesMenu = b; }
    typedef void (*FUNC)(void);
   private:
    bool m_ESCandENTERleavesMenu;
    bool stayInMenu;
    enum style m_alignment;
    tagITEM ** m_menuItems;
    tagMENU * m_menu;
    std::vector<tagITEM *> m_menuItemVector;
    std::vector<FUNC> m_functionToCallVector;
    std::map<tagITEM *, FUNC> m_menuItemMap;
  };
}
