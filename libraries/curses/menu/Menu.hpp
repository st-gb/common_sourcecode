#pragma once //include guard

#include <vector> //class std::vector
#include <map> //class std::map
//#include <libraries/ncurses/InputProcessorStack.hpp>
#include <libraries/curses/windows/Window.hpp>

/** Forward declarations (faster than to #include) */
struct _win_st; //WINDOW

namespace Curses
{
  class Menu
    : public Curses::Window
  {
  public:
    enum style { Vertical, Horizontal};
    typedef void (*FUNC)(void);
   private:
    int m_numRowsNeeded, m_numColumnsNeeded;
    bool m_ESCandENTERleavesMenu;
    bool m_stayInMenu;
    enum style m_alignment;
    WINDOW * m_subMenuWindow;
   public:
//    Menu();
//    ~Menu();
    
    virtual int addMenuItem(const char str [], void (*FUNC)(void) = 0 ) {};
    virtual WINDOW * create(WINDOW * windowToShowMenuIn) {};
    virtual void createMenu(enum style _style = Vertical) {};
//    int HandleAction(const int ch);
//    int InsideMenu(bool = true, WINDOW * windowToShowMenuIn = 0 );
    void SetEnterLeavesMenu(bool b){ m_ESCandENTERleavesMenu = b; }
    int GetNumRowsNeeded() const { return m_numRowsNeeded; }
    int GetNumColumnsNeeded() const { return m_numColumnsNeeded; }
  };
}
