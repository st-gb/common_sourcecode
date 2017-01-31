#include "MessageBox.hpp"
#include <hardware/CPU/fastest_data_type.h> //fastestUnsignedDataType
#include <vector> //class std::vector
#include <sstream> //std::ostringstream
#include <libraries/curses/color.h> //colorBox(...)

namespace Ncurses
{
  MessageBox::MessageBox(chtype colorPair, chtype buttonColorPair)
    : m_colorPair(colorPair), m_buttonColorPair(buttonColorPair)
  { 
  }

  void MessageBox::ShowMessage(const char message [], WINDOW * windowToShowMessageIn)
  {
    const char * currentMessageChar = message;
    int currentLineWidth = 0, maxLineWidth = 0, numLines = 1;
    std::vector<fastestUnsignedDataType> lineLengthes;
    /** Get maximal line lengthes. */
    while( * currentMessageChar != '\0' )
    {
      if( * currentMessageChar == '\n' )
      {
        lineLengthes.push_back(currentLineWidth);
        if( currentLineWidth > maxLineWidth)
          maxLineWidth = currentLineWidth;
        currentLineWidth = 0;
        numLines ++;
      }
      else
        currentLineWidth ++;
      currentMessageChar ++;
    }
    if( currentLineWidth)
      lineLengthes.push_back(currentLineWidth);
    if( currentLineWidth > maxLineWidth)
      maxLineWidth = currentLineWidth;
    
    int oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow;
    getyx(windowToShowMessageIn, oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow);
    int yBeginOfBodyWindow, xBeginOfBodyWindow;
    getbegyx(windowToShowMessageIn, yBeginOfBodyWindow, xBeginOfBodyWindow);
    const int windowHeight = numLines + /** box chars + line for OK button*/ 3;
    /** If window was created with derwin(...) or subwin(...) it isn't cleared 
     *  from screen after wdelete(...). So use newwin(...) instead. */
    WINDOW * p_MessageWindow = newwin(
//      windowToShowMessageIn, 
      windowHeight , 
      maxLineWidth + 2, 1, 1 );
    colorBox(p_MessageWindow, m_colorPair, 1);
    mvwaddstr(p_MessageWindow, 0, 1, "message");
  //  mvwaddstr(p_win, 1, 1, message);
    const char * lineBegin = message, * formatString;
    char recipeString[10];
    for( int i = 0; i < lineLengthes.size(); i++ )
    {
      currentLineWidth = lineLengthes.at(i);
//      std::ostringstream oss;
//      oss << "%." << currentLineWidth << "s"; //-> e.g. "%.20s"
//      formatString = oss.str().c_str();
      sprintf(recipeString, "%%.%ds", currentLineWidth);//-> e.g. "%.20s"
      mvwprintw(p_MessageWindow, 1 + i , 1, recipeString, lineBegin );
      lineBegin += currentLineWidth + 1;
    }
    WINDOW * p_OKwindow = derwin(p_MessageWindow, 1 , 2, windowHeight - 2, 
      maxLineWidth / 2 );
    colorBox(p_OKwindow, m_buttonColorPair, 1);
    mvwaddstr(p_OKwindow, 0, 0, "OK");
    wrefresh(p_OKwindow);
  //  touchwin(s_bodyWindow);
    wrefresh(p_MessageWindow);
    int ch;
    do
    {
      ch = wgetch(p_MessageWindow);
      /** https://linux.die.net/man/3/wgetch :
       * "In no-delay mode, if no input is waiting, the value ERR is returned."
       * ERR = no valid input. */
  //    if( ch != ERR )
    }while(ch != '\n' );
    delwin(p_OKwindow);
    delwin(p_MessageWindow);
    touchwin(windowToShowMessageIn);
//    wmove(windowToShowMessageIn, oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow);
    wrefresh(windowToShowMessageIn);    
  }
}
