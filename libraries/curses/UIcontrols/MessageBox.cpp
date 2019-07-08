#include "MessageBox.hpp"
#include "hardware/CPU/atomic/AtomicExchange.h"
//TODO remove the dependency to the following file
#include "ncurses/MainWindow.hpp"
//#include "hardware/CPU/atomic/memory_barrier.h"
#include <hardware/CPU/fastest_data_type.h> //fastestUnsignedDataType
#include <vector> //class std::vector
#include <sstream> //std::ostringstream
#include <libraries/curses/color.h> //colorBox(...)
#include <libraries/curses/LayoutManager/BorderLayout.hpp> //class BorderLayout
#include <libraries/curses/UIcontrols/Button.hpp> //class curses::Button
#include <string.h> //strlen(...)

/** preprocessor macro "MessageBox" from Windows API */
#undef MessageBox

namespace curses
{
  MessageBox::MessageBox(chtype colorPair, chtype buttonColorPair)
    : //m_windowHandle(NULL), 
      m_p_buttonWindow(NULL),
      m_showWindow(true),
      m_colorPair(colorPair), 
      m_buttonColorPair(buttonColorPair)
  {
    BuildGUI();
  }

  //TODO
  void MessageBox::BuildGUI()
  {
    p_outerLayout = new curses::BorderLayout();
    p_borderLayout = new curses::BorderLayout();
    curses::Button * p_okButton = new curses::Button();
    p_okButton->create();
    p_okButton->SetLabel("OK");
    
    p_textBox = new curses::TextBox(BODY_WINDOW_COLOR);
    p_textBox->SetDrawBorder(false);
    p_textBox->create();
    
    p_borderLayout->add(p_textBox, curses::BorderLayout::center);
    p_borderLayout->add(p_okButton, curses::BorderLayout::bottom);
    p_okButton->SetFocus(true);
    
    /** Add space to the outer regios in order to get a visible border. */
    p_outerLayout->add(p_borderLayout, curses::BorderLayout::center);
    p_outerLayout->add(new Curses::Window(), curses::BorderLayout::top);
    p_outerLayout->add(new Curses::Window(), curses::BorderLayout::bottom);
    p_outerLayout->add(new Curses::Window(), curses::BorderLayout::left);
    p_outerLayout->add(new Curses::Window(), curses::BorderLayout::right);
    
    p_borderLayout->create();
    setLayout(p_outerLayout);
//    p_textBox->show();
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

  int MessageBox::HandleAction(const int ch)
  {
    if(ch == 0xA /* Return- bzw. Enter-Taste -> ASCII-Code */)
    {
      return Curses::Window::destroyWindow;
    }
    return Curses::Window::inputNotHandled;
  }
  
  void MessageBox::ShowMessageText(
    const char message [],
    const std::vector<fastestUnsignedDataType> & lineLengthes,
    const fastestUnsignedDataType windowWidthMinus2)
  {
    m_showWindow = true;
    int currentLineWidth = 0;
    const char * lineBegin = message, * formatString;
    char recipeString[10];
    int currentLineNumber = 1;
    for( int currentLineLengthIndex = 0; currentLineLengthIndex < 
      lineLengthes.size(); currentLineLengthIndex++ )
    {
      currentLineWidth = lineLengthes.at(currentLineLengthIndex);
      if( currentLineWidth > windowWidthMinus2 )
      {
        while(currentLineWidth > windowWidthMinus2)
        {
          sprintf(recipeString, "%%.%ds", windowWidthMinus2);//-> e.g. "%.20s"
          mvwprintw(m_windowHandle, currentLineNumber, 1, recipeString, 
            lineBegin);
          lineBegin += windowWidthMinus2 + 1;
          currentLineWidth -= (windowWidthMinus2);
          currentLineNumber ++;
        }
//        sprintf(recipeString, "%%.%ds", windowWidth);//-> e.g. "%.20s"
//        mvwprintw(m_p_MessageWindow, currentLineNumber, 1, recipeString, 
//          lineBegin);
      }
//      std::ostringstream oss;
//      oss << "%." << currentLineWidth << "s"; //-> e.g. "%.20s"
//      formatString = oss.str().c_str();
//      else
//      {
        sprintf(recipeString, "%%.%ds", currentLineWidth);//-> e.g. "%.20s"
        mvwprintw(m_windowHandle, currentLineNumber, 1, recipeString, 
          lineBegin );
        lineBegin += currentLineWidth + 1;
        currentLineNumber ++;
//      }
    }
  }
  
  void MessageBox::CreateCenteredButton(const char label [], 
    const int numberOfTextLines)
  {
    int windowHeight, windowWidth;
    getmaxyx(m_windowHandle, windowHeight, windowWidth);
    int buttonWidth = strlen(label);
    m_p_buttonWindow = derwin(m_windowHandle, /* height*/ 1 , 
      buttonWidth, windowHeight - 2, 
      (windowWidth - buttonWidth) / 2 );
    colorBox(m_p_buttonWindow, m_buttonColorPair, 0);
    mvwaddstr(m_p_buttonWindow, 0, 0, label);
    wrefresh(m_p_buttonWindow);
  }
  
  void MessageBox::DrawBorderAndTitle()
  {
    colorBox(m_windowHandle, m_colorPair, 1);
    mvwaddstr(m_windowHandle, 0, 1, "message");
  }
  
  int MessageBox::BuildUserInterface(const char message [])
  {
    int maxLineWidth = 0/*, numLines = 1*/;
    std::vector<fastestUnsignedDataType> lineLengthes;
    DetermineMessageTextWidthAndHeight(message, maxLineWidth, lineLengthes );
    //TODO: change to actual # of lines. (if a text line does not fit into a 
    // window line, then there are multiple lines
    int numberOfTextLines = lineLengthes.size();
    
    int windowWidth, superordinateWinHeight; 
    getmaxyx(m_p_windowToShowMessageIn, superordinateWinHeight, windowWidth);
    if( maxLineWidth + 2 < windowWidth)
      windowWidth = maxLineWidth + 2;
    int oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow;
    getyx(m_p_windowToShowMessageIn, oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow);
    int yBeginOfBodyWindow, xBeginOfBodyWindow;
    getbegyx(m_p_windowToShowMessageIn, yBeginOfBodyWindow, xBeginOfBodyWindow);
    const int windowHeight = /*numLines*/ lineLengthes.size() + 
      /** box chars + line for the button*/ 3;
    /** If window was created with derwin(...) or subwin(...) it isn't cleared 
     *  from screen after wdelete(...). So use newwin(...) instead. */
    m_windowHandle = newwin(
//      windowToShowMessageIn, 
      windowHeight , 
      windowWidth, 1, 0 );
    DrawBorderAndTitle();
  //  mvwaddstr(p_win, 1, 1, message);
    /*int numberOfTextLines =*/ ShowMessageText(
      message, 
      lineLengthes, 
      windowWidth - 2);
    return numberOfTextLines;
  }
  
  void MessageBox::determineWindowSize(const char message [])
  {
    int superOrdinateWindowWidth, superordinateWinHeight; 
    getmaxyx(m_p_windowToShowMessageIn, superordinateWinHeight, superOrdinateWindowWidth);
    const int textlineWidth = superOrdinateWindowWidth - 2;
    
    const unsigned textLength = strlen(message);
//    p-
    int numCharsInCurrentWindowLine;
    int numCharsToAdvance;
    int numCharsInCurrentTextLine;
    int charIndexOfTextLineEnd;
    int numberOfWindowLines = 0;
    
    const char * p_windowLineBegin = message;
    const char * lastChar = message + textLength;
    const char * p_textLineBegin = message;
  //  std::string currentLine;
    while( p_windowLineBegin < lastChar )
    {
      const char * p_textLineEnd = strchr(p_windowLineBegin, '\n');
      /** No newline character found. */
      if( p_textLineEnd == NULL )
        p_textLineEnd = message + textLength;
      charIndexOfTextLineEnd = //m_content.find('\n', 
        //handleCurrentLineParams.p_windowLineBegin - m_content.c_str() );
        p_textLineEnd - message;
      if( p_textLineEnd != NULL && p_windowLineBegin == p_textLineBegin )
        numCharsInCurrentTextLine = p_textLineEnd - p_textLineBegin;

      numCharsInCurrentWindowLine = p_textLineEnd - p_windowLineBegin;

  //    currentLine = std::string(currentChar, numCharsInCurrentWindowLine);
      /** "<=" because also advance including the newline if a newline ends at 
         line end. (else an additional empty line would be displayed afterwards.*/
      if(numCharsInCurrentWindowLine <= textlineWidth )
      {
        p_textLineBegin = p_textLineEnd + 1;
        numCharsToAdvance = numCharsInCurrentWindowLine + 1;
        /** -> do NOT print newline chars! */
//        handleCurrentLineParams.numCharsToPrint = numCharsInCurrentWindowLine;
      }
      else
      {
        numCharsToAdvance = textlineWidth;
//        handleCurrentLineParams.numCharsToPrint = numCharsToAdvance;
      }
  //    currentXpos += m_lineWidth;
      p_windowLineBegin += numCharsToAdvance;
      numberOfWindowLines ++;
    }
    const int messageWindowHeightToDisplayAllText = numberOfWindowLines + 3;
    int yBeginOfBodyWindow, xBeginOfBodyWindow;
    getbegyx(m_p_windowToShowMessageIn, yBeginOfBodyWindow, xBeginOfBodyWindow);
    const int windowHeight = messageWindowHeightToDisplayAllText < 
      superordinateWinHeight ? messageWindowHeightToDisplayAllText : 
      superordinateWinHeight;
    m_windowHandle = newwin( windowHeight, 
      superOrdinateWindowWidth, yBeginOfBodyWindow, xBeginOfBodyWindow );
    p_outerLayout->setHandle(m_windowHandle);
    p_outerLayout->layout();
  }
  
  //TODO: make as curses::BorderLayout with curses::TextBox + curses::Button
  void MessageBox::ShowMessage(const char message [], WINDOW * p_windowToShowMessageIn)
  {
    m_p_windowToShowMessageIn = p_windowToShowMessageIn;
//    const int numberOfTextLines = BuildUserInterface(message);
//    CreateCenteredButton("OK", numberOfTextLines);
    p_textBox->SetText(message);
    determineWindowSize(message);
    DrawBorderAndTitle();
    p_borderLayout->showAllContainedWindows();
    
//    touchwin(p_windowToShowMessageIn);
//    wrefresh(p_windowToShowMessageIn);
    wrefresh(m_windowHandle);
//    wgetch(m_p_MessageWindow); /** -> modal */
    s_inputProcessorStack.add(this);
    /** Ensures modality of this dialog. */
    Curses::EventLoop(false);
  }
  
  void MessageBox::EventLoop()
  {
    int ch;
    do
    {
      ch = wgetch(m_windowHandle);
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
    if(m_windowHandle != NULL && m_p_buttonWindow != NULL)
    {
      delwin(m_p_buttonWindow);
      delwin(m_windowHandle);
      touchwin(m_p_windowToShowMessageIn);
  //    wmove(windowToShowMessageIn, oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow);
      wrefresh(m_p_windowToShowMessageIn);
    }
  }
}
