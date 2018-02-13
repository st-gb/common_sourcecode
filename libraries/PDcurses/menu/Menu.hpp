#pragma once //include guard

#include <libraries/curses/menu/Menu.hpp>
#include <hardware/CPU/fastest_data_type.h>

/** Forward declarations (faster than to #include) */
struct _win_st; //WINDOW

namespace PDcurses
{
//  typedef void (*FUNC)(void);
  struct MenuLabelAndFunction
  {
    std::string m_label;
    Curses::Menu::FUNC m_function;
  };
  
  class Menu
    : public Curses::Menu
  {
  public:
    typedef std::vector<MenuLabelAndFunction> MenuLabelAndFunctionType;
   private:
    std::vector<FUNC> m_functionToCallVector;
    MenuLabelAndFunctionType m_menuLabelAndFunction;
    fastestUnsignedDataType m_currentMenuItem;
   public:
    Menu();
    ~Menu();
    int addMenuItem(const char str [], void (*FUNC)(void) = NULL );
    int checkUniqueAcceleratorKey(const char name[]);
//    void createMenu();
    MenuLabelAndFunctionType & GetMenuLabelAndFunctionVector() { return m_menuLabelAndFunction;}
    int HandleAction(int currentAction);
    int InsideMenu(bool, WINDOW * windowToShowMenuIn = NULL );
  };
}
