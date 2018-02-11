#pragma once//Include guard

#include "../windows/Window.hpp" //class Ncurses::Window
#include <curses.h> //WINDOW
#include <hardware/CPU/fastest_data_type.h> //fastestUnsignedDataType

namespace Curses
{
  class MessageBox
    : public Curses::Window
  {
  private:
    WINDOW * m_p_buttonWindow;
  protected:
    WINDOW * m_p_MessageWindow, * m_p_windowToShowMessageIn;
    chtype m_colorPair, m_buttonColorPair;
    /*volatile*/ bool m_showWindow;
  public:
    MessageBox(chtype colorPair, chtype buttonColorPair);
    virtual void ShowMessage(const char message [], WINDOW * windowToShowMessageIn);
    void CreateCenteredButton(const char label [], const int numberOfTextLines);
    int BuildUserInterface(const char message []);
    void Close();
    void Destroy();
    virtual void EventLoop();
    void ShowMessageText(
      const char message [],
      const std::vector<fastestUnsignedDataType> &,
      const fastestUnsignedDataType windowWidth);
  };
}