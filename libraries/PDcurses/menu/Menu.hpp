#pragma once //include guard

#include <libraries/curses/menu/Menu.hpp>
#include <hardware/CPU/fastest_data_type.h>
#include <string> //class std::string
#include <libraries/curses/menu/MenuLabelAndFunction.hpp>

/** Forward declarations (faster than to #include) */
struct _win_st; //WINDOW

namespace PDcurses
{
//  typedef void (*FUNC)(void);  
  class Menu
    : public curses::Menu
  {
  public:
    typedef std::vector<curses::MenuLabelAndFunction> MenuLabelAndFunctionType;
   private:
    std::vector<curses::FUNC> m_functionToCallVector;
    MenuLabelAndFunctionType m_menuLabelAndFunction;
    fastestUnsignedDataType m_currentMenuItem;
    WINDOW * m_windowHandle;
   public:
    Menu(ncurses::WindowHandleWindow * win);
    ~Menu();
    int addMenuItem(const char str [], void (*FUNC)(void) = NULL );
    WINDOW * create(WINDOW * windowToShowMenuIn);
    int checkUniqueAcceleratorKey(const char name[]);
//    void createMenu();
    MenuLabelAndFunctionType & GetMenuLabelAndFunctionVector() { return m_menuLabelAndFunction;}
    int HandleAction(int currentAction);
    int InsideMenu(bool, WINDOW * windowToShowMenuIn = NULL );
    void show();
  };
}
