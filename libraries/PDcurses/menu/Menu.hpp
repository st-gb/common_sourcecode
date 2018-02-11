#pragma once //include guard

#include <vector> //class std::vector
#include <map> //class std::map

/** Forward declarations (faster than to #include) */
struct tagITEM;
struct tagMENU;
struct _win_st; //WINDOW

namespace PDcurses
{
  class Menu
  {
    typedef void (*FUNC)(void);
   private:
    std::vector<tagITEM *> m_menuItemVector;
    std::vector<FUNC> m_functionToCallVector;
    std::map<tagITEM *, FUNC> m_menuItemMap;
   public:
    Menu();
    ~Menu();
    void addMenuItem(const char str [], void (*FUNC)(void) = NULL );
    void createMenu();
    int InsideMenu(bool, struct _win_st * windowToShowMenuIn = NULL );
  };
}
