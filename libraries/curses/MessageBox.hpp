#pragma once//Include guard

#include "Window.hpp" //class Ncurses::Window
#include <curses.h> //WINDOW

namespace Ncurses
{
  class MessageBox
    : public Ncurses::Window
  {
    chtype m_colorPair, m_buttonColorPair;
  public:
    MessageBox(chtype colorPair, chtype buttonColorPair);
    void ShowMessage(const char message [], WINDOW * windowToShowMessageIn);
  };
}