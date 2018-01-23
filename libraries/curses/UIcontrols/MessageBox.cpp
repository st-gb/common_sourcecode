#include "MessageBox.hpp"
#include "hardware/CPU/atomic/AtomicExchange.h"
//#include "hardware/CPU/atomic/memory_barrier.h"
#include <hardware/CPU/fastest_data_type.h> //fastestUnsignedDataType
#include <vector> //class std::vector
#include <sstream> //std::ostringstream
#include <libraries/curses/color.h> //colorBox(...)
#include <string.h> //strlen(...)

namespace Curses
{
  MessageBox::MessageBox(chtype colorPair, chtype buttonColorPair)
    : m_p_MessageWindow(NULL), 
      m_p_buttonWindow(NULL),
      m_showWindow(true),
      m_colorPair(colorPair), 
      m_buttonColorPair(buttonColorPair)
  { 
  }

  void DetermineMessageTextWidthAndHeight(
    const char message [],
    int & maxLineWidth,
    std::vector<fastestUnsignedDataType> & lineLengthes
    )
  {
    const char * currentMessageChar = message;
    int currentLineWidth = 0;
    /** Get maximal line lengthes. */
    while( * currentMessageChar != '\0' )
    {
      if( * currentMessageChar == '\n' )
      {
        lineLengthes.push_back(currentLineWidth);
        if( currentLineWidth > maxLineWidth)
          maxLineWidth = currentLineWidth;
        currentLineWidth = 0;
//        numLines ++;
      }
      else
        currentLineWidth ++;
      currentMessageChar ++;
    }
    if( currentLineWidth)
      lineLengthes.push_back(currentLineWidth);
    if( currentLineWidth > maxLineWidth)
      maxLineWidth = currentLineWidth;
  }

  void MessageBox::ShowMessageText(
    const char message [],
    const std::vector<fastestUnsignedDataType> & lineLengthes)
  {
    m_showWindow = true;
    int currentLineWidth = 0;
    const char * lineBegin = message, * formatString;
    char recipeString[10];
    for( int i = 0; i < lineLengthes.size(); i++ )
    {
      currentLineWidth = lineLengthes.at(i);
//      std::ostringstream oss;
//      oss << "%." << currentLineWidth << "s"; //-> e.g. "%.20s"
//      formatString = oss.str().c_str();
      sprintf(recipeString, "%%.%ds", currentLineWidth);//-> e.g. "%.20s"
      mvwprintw(m_p_MessageWindow, 1 + i , 1, recipeString, lineBegin );
      lineBegin += currentLineWidth + 1;
    }
  }
  
  void MessageBox::CreateCenteredButton(const char label [])
  {
    int windowHeight, windowWidth;
    getmaxyx(m_p_MessageWindow, windowHeight, windowWidth);
    int buttonWidth = strlen(label);
    m_p_buttonWindow = derwin(m_p_MessageWindow, /* height*/ 1 , buttonWidth, windowHeight - 2, 
      (windowWidth - buttonWidth) / 2 );
    colorBox(m_p_buttonWindow, m_buttonColorPair, 0);
    mvwaddstr(m_p_buttonWindow, 0, 0, label);
    wrefresh(m_p_buttonWindow);
  }
  
  void MessageBox::BuildUserInterface(const char message [])
  {
    int maxLineWidth = 0/*, numLines = 1*/;
    std::vector<fastestUnsignedDataType> lineLengthes;
    DetermineMessageTextWidthAndHeight(message, maxLineWidth, lineLengthes );
    
    int oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow;
    getyx(m_p_windowToShowMessageIn, oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow);
    int yBeginOfBodyWindow, xBeginOfBodyWindow;
    getbegyx(m_p_windowToShowMessageIn, yBeginOfBodyWindow, xBeginOfBodyWindow);
    const int windowHeight = /*numLines*/ lineLengthes.size() + 
      /** box chars + line for the button*/ 3;
    /** If window was created with derwin(...) or subwin(...) it isn't cleared 
     *  from screen after wdelete(...). So use newwin(...) instead. */
    m_p_MessageWindow = newwin(
//      windowToShowMessageIn, 
      windowHeight , 
      maxLineWidth + 2, 1, 1 );
    colorBox(m_p_MessageWindow, m_colorPair, 1);
    mvwaddstr(m_p_MessageWindow, 0, 1, "message");
  //  mvwaddstr(p_win, 1, 1, message);
    ShowMessageText(message, lineLengthes);
  }

  void MessageBox::ShowMessage(const char message [], WINDOW * p_windowToShowMessageIn)
  {
    m_p_windowToShowMessageIn = p_windowToShowMessageIn;
    BuildUserInterface(message);
    CreateCenteredButton("OK");
  //  touchwin(s_bodyWindow);
    wrefresh(m_p_MessageWindow);
  }
  
  void MessageBox::EventLoop()
  {
    int ch;
    do
    {
      ch = wgetch(m_p_MessageWindow);
//      hardwareFence();
      /** https://linux.die.net/man/3/wgetch :
       * "In no-delay mode, if no input is waiting, the value ERR is returned."
       * ERR = no valid input. */
  //    if( ch != ERR )
    }while(ch != '\n' && m_showWindow );
//    if( ch == '\n')
    Destroy();
  }

  void MessageBox::Close()
  {
//    AtomicExchange( (long int *) & m_showWindow, false);
    m_showWindow = false;
  }
  
  void MessageBox::Destroy()
  {
    if(m_p_MessageWindow != NULL && m_p_buttonWindow != NULL)
    {
      delwin(m_p_buttonWindow);
      delwin(m_p_MessageWindow);
      touchwin(m_p_windowToShowMessageIn);
  //    wmove(windowToShowMessageIn, oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow);
      wrefresh(m_p_windowToShowMessageIn);
    }
  }
}
