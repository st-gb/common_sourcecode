
#include <curses.h> // WINDOW
#include <string> //class std::string
#include <hardware/CPU/fastest_data_type.h>
#include "../textfield.h"
#include "../color.h"
#include <libraries/curses/curs_set_constants.h>
#include "TextBox.hpp"
#include <libraries/curses/windows/Window.hpp>
#include "drawScrollBar.h"
#include <string.h> //strcmp(...)
#include "CursorPosChangedListener.hpp" //class curses::CurorPosChangedListener

/** Following code is from PDCurses-3.4/demos/tui.c, tui.h */
 
#define KEY_ESC    0x1b  /** "Esc" key */
#define KEY_BKSP   0x8   /** "<-" key */

#ifndef PDCURSES
static char wordchar(void)
{
    return 0x17;    /* ^W */ 
}
#endif

static void repaintEditbox(WINDOW *win, int curserPos, const char buffer[] )
{
#ifndef PDCURSES
    int maxy;
#endif
    int windowWidth;

#ifdef PDCURSES
    windowWidth = getmaxx(win);
#else
    getmaxyx(win, maxy, windowWidth);
#endif
    werase(win);
//    mvwprintw(win, 0, 0, "%s", /*padStr(buffer, maxX)*/ buffer );
    mvwaddstr(win, 0, 0, buffer );
    int yPos = curserPos / windowWidth;
    int xPos = curserPos == 0 ? 0 : curserPos % windowWidth;
    /** https://www.ibm.com/support/knowledgecenter/en/ssw_aix_61/com.ibm.aix.genprogc/control_cursor_wcurses.htm :
     *  "Moves the logical cursor associated with a user-defined window" */
    wmove(win, yPos, xPos);
    wrefresh(win);
}

namespace curses
{
/*  weditstr()     - edit string 
 * Description:
    The initial value of 'str' with a maximum length of 'field' - 1,
    which is supplied by the calling routine, is editted. The user's 
    erase (^H), kill (^U) and delete word (^W) chars are interpreted. 
    The PC insert or Tab keys toggle between insert and edit mode.
    Escape aborts the edit session, leaving 'str' unchanged.
    Enter, Up or Down Arrow are used to accept the changes to 'str'.
    NOTE: editstr(), mveditstr(), and mvweditstr() are macros.

  Return Value:
    Returns the input terminating character on success (Escape, 
    Enter, Up or Down Arrow) and ERR on error.

  Errors:
    It is an error to call this function with a NULL window pointer.
    The length of the initial 'str' must not exceed 'field' - 1. */

/** Constructor for cases if width and height is unknown. */
TextBox::TextBox(
//  WINDOW * p_superWindow, 
//  const std::string & std_strContent, 
  chtype colorPair
  )
//  : m_p_superWindow(NULL)//p_superWindow)
//    , p_editWindow(NULL)
   //, m_content(std_strContent)
  : m_drawBorder(true),
    m_editable(false),
//    m_colorPair(colorPair),
    m_lineWidth(0),
    m_cursorPos(0),
    m_1stLineToShow(0),
    m_numVisibleLinesForText(0),
    m_colorPair(colorPair),
    m_cursorLineBeginCharIndex(0),
    m_1stLineToShowBeginCharIndex(0)
{
}

//void TextBox::create()
//{
//  
//}

void TextBox::create(WINDOW * const p_superWindow, 
  int numLines, int numColumns, int x, int y)
{
  m_p_superWindow = p_superWindow;
//  int cury, curx, begy, begx;
  /** http://pubs.opengroup.org/onlinepubs/7908799/xcurses/doupdate.html
  * "refresh the current or specified window." */
  wrefresh(p_superWindow);
//  getyx(p_superWindow, cury, curx);
//  getbegyx(p_superWindow, begy, begx);
  /** If window was created with derwin(...) or subwin(...) it isn't cleared
   *  from screen after wdelete(...). So use newwin(...) instead. */
  /*p_editWindow*/ m_windowHandle = //subwin( p_superWindow,
    Curses::Window::CreateWindowRelativePos(
    p_superWindow,
    numLines,
    numColumns /* number of colums */, 
    y, //begy + cury,
    x //begx + curx
    );
  //TODO is NULL when (indirectly) called from changePartitionTableOffsets(...)
  if( ! /*p_editWindow*/ m_windowHandle )
    return;
  m_oldAttribute = /*p_editWindow*/m_windowHandle->_attrs;
  //TODO change EDITBOXCOLOR to m_colorPair?!
  colorBox( /*p_editWindow*/ m_windowHandle, EDITBOXCOLOR, 0);

  /** http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/init.html
   *  "enables the reading of function keys like F1, F2, arrow keys etc." */
  keypad( /*p_editWindow*/ m_windowHandle, TRUE); /** Enable cursor keys */
}

TextBox::~TextBox()
{
  if( /*p_editWindow*/ m_windowHandle)
  {
    wattrset( /*p_editWindow*/ m_windowHandle, m_oldAttribute);
  //  repaintEditbox( p_editWindow, bufferPointer - buffer, buffer);
//    delwin( /*p_editWindow*/ m_windowHandle);
    touchwin(m_p_superWindow);
    wrefresh(m_p_superWindow);
  }
}

void TextBox::GetMinimalSize(int & width, int & height) {
  if(m_drawBorder)
  {
    width = 3; 
    height = 3;
  }
  else
  {
    width = 1; 
    height = 1;
  }
}

int TextBox::handleEdit(const int currentInput, int & cursor_mode)
{
  const char eraseCharacter = erasechar(); /** curses function */
  const char killCharacter = killchar(); /** curses function */
    switch( currentInput )
    {
    case '\n':
//    case KEY_UP:
//    case KEY_DOWN:
        stop = TRUE;
        break;
    case KEY_DC: //Delete Character
      //TODO string length check needed?
      m_content.erase(m_cursorPos, /** Only erase 1 character. */ 1  );
      show();
      break;
    case KEY_BKSP:
    case KEY_BACKSPACE:
      if( m_cursorPos > 0)
      {
        m_content.erase( -- m_cursorPos, /** Only erase 1 character. */ 1 );
        show();
      }
      break;
//    case '\t':            /* TAB -- because insert
//                              is broken on HPUX */
    case KEY_IC:          /* enter insert mode */
    case KEY_EIC:         /* exit insert mode */
      defdisp = FALSE;
      insertMode = !insertMode; /**Switch the insert mode*/
      cursor_mode = insertMode ? 
        curses::Cursor::Terminal_specific_high_visibility_mode : 
        curses::Cursor::Terminal_specific_normal_mode;
      cursor_mode = curs_set(cursor_mode); /**set the cursor mode*/
      break;
    default:
//      {int i = 0;}
      /** Backspace in Ubuntu with curses is "263" 263-256=7*/
      if(currentInput - 256 == eraseCharacter )/* backspace, ^H */
      {
      }
      else if (currentInput == killCharacter )   /* ^U */
      {
        m_cursorPos = 0;
        m_content.clear();
        show();
      }
      else if(currentInput == wordchar() )   /* ^W */
      {
        int charPosAfterWord = m_cursorPos;
        while( (m_cursorPos > 0) && ( m_content.at(m_cursorPos - 1) == ' ') )
          m_cursorPos --;
        while( (m_cursorPos > 0) && ( m_content.at(m_cursorPos - 1) != ' ') )
          m_cursorPos --;
        /** Remove all characters between cursorPos and charPosAfterWord */
        m_content.erase(m_cursorPos, charPosAfterWord - m_cursorPos);
        show();
      }
      else if (isprint(currentInput) ) /** If printable character. */
      {
        if (defdisp)
        {
          m_cursorPos = 0;
          m_content.clear();
          show();
          defdisp = FALSE;
        }
        if (insertMode == insertChar )
        {
          /** Avoids runtime error: "terminate called after throwing an instance of 
           *     'std::out_of_range'" what():  basic_string::insert */
          if( m_cursorPos <= m_content.length() )
          {
            m_content.insert(m_cursorPos ++, 1, (char) currentInput);
            show();
          }
        }
        else if( m_cursorPos < numColumns - 1)
        {
          if( m_cursorPos == m_content.size() ) //if cursor is at last char 
              m_content += currentInput; //append character.
          else //Overwrite char
            m_content.at(m_cursorPos ++) = currentInput;
          show();
        }
      }
      else
        return Curses::Window::inputNotHandled;
    }
    return currentInput;
}

void TextBox::ShowCursorPos()
{
  int maxy;
  int maxx;
#ifdef PDCURSES
  maxy = getmaxy(m_windowHandle);
  maxx = getmaxx(m_windowHandle);
#else
  getmaxyx(m_windowHandle, maxy, maxx);
#endif
//  const int lineWidth = m_drawBorder ? maxx - 2 : maxx; 
  //TODO this works only if there is no newline in the text
//  int cursorY = (m_cursorPos - m_lineWidth * m_1stLineToShow) / lineWidth;  
//  int cursorX = m_cursorPos % lineWidth;
 
  const char * beginOfString = m_content.c_str();
#ifdef _DEBUG
  const int textSize = m_content.size();
#endif
  char currentChar;
  int beginOfLineCharIndex = 0;
  int currentCharPos = 0;
  int cursorX, cursorY = 0;
  int lineNumber = 0;
  int previousChar = -1;
//  int lastAutomaticLineBreakCharIndex = -1;
  for( ; currentCharPos < textSize; currentCharPos ++ )
  {
    //TODO SIGSEGV here when at end of text
    currentChar = *(beginOfString + currentCharPos);
    if(/*beginOfString + currentCharPos - beginOfLine*/
        (currentCharPos - beginOfLineCharIndex ) == m_lineWidth)
    {
//      beginOfLine = /*p_currentChar*/ beginOfString + currentCharPos + 1;
      beginOfLineCharIndex = currentCharPos;
//      lastAutomaticLineBreakCharIndex = currentCharPos;
      lineNumber ++;
    }
    else
      //!---TODO
      if( previousChar == '\n' /*&& lastAutomaticLineBreakCharIndex*/ )
      {
        beginOfLineCharIndex = currentCharPos /*+ 1*/;
        lineNumber ++;
      }
    previousChar = currentChar;
    if( m_cursorPos == currentCharPos)
    {
      cursorX = currentCharPos - beginOfLineCharIndex;
      cursorY = lineNumber - m_1stLineToShow;
      break;
    }
  }
  
  /** https://www.ibm.com/support/knowledgecenter/en/ssw_aix_61/com.ibm.aix.genprogc/control_cursor_wcurses.htm :
   *  "Moves the logical cursor associated with a user-defined window" */
  wmove(m_windowHandle, cursorY + m_drawBorder, cursorX + m_drawBorder);
  /** Finally updated the cursor position visually. */
  wrefresh(m_windowHandle);
}

void TextBox::AddCursorPosChangedListener(
  curses::CursorPosChangedListener * p_cursorPosChangedListener)
{
  p_cursorPosChangedListener->SetTextBox(this);
  m_cursorPosChangedListenerContainer.push_back(p_cursorPosChangedListener);
}

void TextBox::NotifyCursorPosChangedListener()
{
  for( CursorPosChangedListenerContainerType::const_iterator cIter = 
    m_cursorPosChangedListenerContainer.begin(); cIter != 
    m_cursorPosChangedListenerContainer.end(); cIter++)
  {
    (*cIter)->Notify();
  }
}

void TextBox::HandleCtrlLeftKey()
{
  const char * currentStringPointer = m_content.c_str() + m_cursorPos;
  bool spaceCharReached = false;
  for( ; currentStringPointer != m_content.c_str(); currentStringPointer-- )
  {
    if( *currentStringPointer == ' ' )
    {
      spaceCharReached = true;
    }
    else
      if(spaceCharReached)
      {
        m_cursorPos = currentStringPointer - m_content.c_str();
        NotifyCursorPosChangedListener();
        ShowCursorPos();
        break;
      }
  }
}

void TextBox::HandleCtrlRightKey()
{
  const char * currentStringPointer = m_content.c_str() + m_cursorPos;
  bool spaceCharReached = false;
  for( ; *currentStringPointer != '\0'; currentStringPointer++ )
  {
    if( *currentStringPointer == ' ' )
    {
      spaceCharReached = true;
    }
    else
      if(spaceCharReached)
      {
        m_cursorPos = currentStringPointer - m_content.c_str();
        NotifyCursorPosChangedListener();
        ShowCursorPos();
        break;
      }
  }
}

//@return: number of characters to subtract from line width 
//       this value is for "key up", but not for "key left".
int TextBox::GetBeginOfWindowLine(int currentCharPos, 
  int & numCharsToSubtractFromLineWidth )
{
//  int numCharsToSubtractFromLineWidth = 0;
  int newCursorLineBeginCharIndex = 0;
//    bool cursorPosChanged = false;
    const int newCurrentCursorLineEndCharIndex = currentCharPos;
    int beginOfNewCurrentLine = -1;
    for(; currentCharPos > -1 ; currentCharPos --)
    {
//      if( numNewLinesToLookFor == 1)
//      {
        if( m_content[currentCharPos] == '\n')
          beginOfNewCurrentLine = currentCharPos + 1;
        if( currentCharPos == 0)
          beginOfNewCurrentLine = currentCharPos;
          if( beginOfNewCurrentLine > -1 )
          {
//            const int beginOfNewCurrentLine = currentCharPos + 1;
            const int numCharsInNewCurrentLine = newCurrentCursorLineEndCharIndex - 
              beginOfNewCurrentLine + 1;
            int numCharsInNewCurrentCursorLine;
            /** void % by 0 error */
            if( numCharsInNewCurrentLine > 0)
              /** The remainder of modulo ist the # chas in previous window line */
              numCharsInNewCurrentCursorLine = m_lineWidth % 
                numCharsInNewCurrentLine;
            else
              numCharsInNewCurrentCursorLine = 0;
            const int cursorXpos = m_cursorPos - m_cursorLineBeginCharIndex;
//            lineBeginCharIndex = currentCharPos + 1;
            if( numCharsInNewCurrentCursorLine < cursorXpos)
            {
                newCursorLineBeginCharIndex -= (numCharsInNewCurrentLine 
                  /** newline char*/ + 1);
                numCharsToSubtractFromLineWidth = (numCharsInNewCurrentCursorLine
                  /** newline char*/ + 1 );
//                cursorPosChanged = true;
                break;
            }
            else
            {
                newCursorLineBeginCharIndex -= m_lineWidth;
//                m_cursorPos -= (m_lineWidth - cursorXpos);
                numCharsToSubtractFromLineWidth = cursorXpos;
//                cursorPosChanged = true;
                break;
            }
//            numLines ++;
//            if( numLines == m_numVisibleLinesForText )
//              return currentCharPos /*- m_1stLineToShowBeginCharIndex*/;
         }
      }
//      else
//        numNewLinesToLookFor--;
//    }
//  return /*cursorPosChanged*/ numCharsToSubtractFromLineWidth;
  return newCursorLineBeginCharIndex;
}

void TextBox::HandleKeyUp()
{
  bool cursorPosChanged = false;
  int cursorX = m_cursorLineBeginCharIndex - m_cursorPos;
  if(m_cursorLineBeginCharIndex > 0)
  {
//    int numNewLinesToLookFor;
    int currentCharPos = m_cursorLineBeginCharIndex - 1;
    /** New window line was causes by a newline character (and not by an
     *  automatic line break). */
    if( m_content[currentCharPos] == '\n')
    {
//       numNewLinesToLookFor = 2;
      int numCharsToSubtractFromLineWidth;
      /*cursorPosChanged*/ 
      m_cursorLineBeginCharIndex = GetBeginOfWindowLine(
        currentCharPos - 1, numCharsToSubtractFromLineWidth);
      m_cursorPos -= m_lineWidth - numCharsToSubtractFromLineWidth;
    }
    else
    {
       if( m_cursorLineBeginCharIndex >= m_lineWidth )
       {
        m_cursorLineBeginCharIndex -= m_lineWidth;
        m_cursorPos -= (m_lineWidth - cursorX);
 //       numNewLinesToLookFor = 1;
        cursorPosChanged = true;
       }
    }
  }
  if (cursorPosChanged)
  {
    NotifyCursorPosChangedListener();
    if (m_cursorPos < m_1stLineToShowBeginCharIndex )
    {
      m_1stLineToShow--;
      show();
    }
    ShowCursorPos();
  }
}
 
int TextBox::GetLastVisibleWindowLineEndCharIndex()
{
    int numLines = 0;
    int lineBeginCharIndex = m_1stLineToShowBeginCharIndex;
    for(int currentCharPos = m_1stLineToShowBeginCharIndex; 
        currentCharPos < m_content.size() ; currentCharPos ++)
    {
      if( m_content[currentCharPos] == '\n' || 
          currentCharPos - lineBeginCharIndex > m_lineWidth )
      {
          lineBeginCharIndex = currentCharPos + 1;
          numLines ++;
          if( numLines == m_numVisibleLinesForText )
            return currentCharPos /*- m_1stLineToShowBeginCharIndex*/;
      }
    }
    return -1;
}

void TextBox::HandleKeyDown(const int ch)
{
  const int textLength = m_content.length();
//  char p_currentChar = m_content.c_str() + m_cursorPos;
  /** If at least 1 line left after cursor position. */
//  if(textLength > m_lineWidth && m_cursorPos < textLength - m_lineWidth)
  int currentCharPos = m_cursorPos;
  int previousCursorPos = m_cursorPos;
//  int lineBegin = 
  int currentX = -1;
  int currentXpos = m_cursorPos - m_cursorLineBeginCharIndex;
  bool newCursorPosSet = false;
//  m_cursorLineBeginCharIndex = 0;
  bool lineEndForCurrentCursorPosFound = false;
  for( ; currentCharPos < m_content.size() ; currentCharPos ++)
  {
//    m_cursorPos += m_lineWidth;
    if( m_content[currentCharPos] == '\n')
      if( lineEndForCurrentCursorPosFound)
      {
        //TODO does not work for "\n\n" ?!
        //TODO last char fits exactly into window line and newline char directly afterwards
        /** New cursor pos points to the index of the newline char. */
        m_cursorPos = currentCharPos;
        newCursorPosSet = true;
        break;
      }
      else
      {
        m_cursorLineBeginCharIndex = currentCharPos + 1;
        lineEndForCurrentCursorPosFound = true;
      }
    if(currentCharPos - m_cursorLineBeginCharIndex == m_lineWidth )
    {
      if( lineEndForCurrentCursorPosFound)
        ;
      else
      {
        lineEndForCurrentCursorPosFound = true;
        m_cursorLineBeginCharIndex = currentCharPos;
      }
    }
    if( lineEndForCurrentCursorPosFound && 
       currentCharPos == m_cursorLineBeginCharIndex + currentXpos )
    {
      m_cursorPos = currentCharPos;
      newCursorPosSet = true;
      break;
    }
//    if( currentCharPos == m_cursorPos )
//    {
//      currentX = currentCharPos - m_cursorLineBeginCharIndex;        
//    }
  }
//  if( currentX > -1 )
//  {
//    for( ; currentCharPos < m_content.size() ; currentCharPos ++)
//    {
//  //    m_cursorPos += m_lineWidth;
////      if( m_content[currentCharPos] == '\n' || 
////        m_cursorLineBeginCharIndex - currentCharPos > m_lineWidth )
////      {
////        m_cursorPos = currentCharPos;
////        newCursorPosSet = true;
////        break;
////      }
//      if( currentCharPos - m_cursorLineBeginCharIndex == currentX )
//      {
//        m_cursorPos = currentCharPos;
//        newCursorPosSet = true;
//        break;
//      }
//    }
    if( newCursorPosSet)
    {
        NotifyCursorPosChangedListener();
        const int lastVisibleWindowLineEndCharIndex = 
          GetLastVisibleWindowLineEndCharIndex();        
        //TODO check the following line
        if( lastVisibleWindowLineEndCharIndex > -1 && 
            previousCursorPos <= lastVisibleWindowLineEndCharIndex &&
            m_cursorPos > lastVisibleWindowLineEndCharIndex )
        {
          //TODO also calculate new m_1stLineToShowBeginCharIndex!
          m_1stLineToShow++;
          show();
        }
        ShowCursorPos();
    }
//  }
}

void TextBox::HandleKeyPreviousPage()
{
  const int numCharsToSubtract = m_numVisibleLinesForText * m_lineWidth;
  if (m_cursorPos >= numCharsToSubtract )
  {
    m_cursorPos -= numCharsToSubtract;
    NotifyCursorPosChangedListener();
    if( m_1stLineToShow >= m_numVisibleLinesForText)
      m_1stLineToShow -= m_numVisibleLinesForText;
    else
      m_1stLineToShow = 0;
    show();
    ShowCursorPos();
  }
}

void TextBox::HandleKeyNextPage()
{
  const int textLength = m_content.length();
  if(m_cursorPos < textLength - (m_lineWidth * m_numVisibleLinesForText) )
  {
    m_cursorPos += m_lineWidth * m_numVisibleLinesForText;
    NotifyCursorPosChangedListener();
    m_1stLineToShow += m_numVisibleLinesForText;
    show();
  }
}

void TextBox::HandleLeftArrowKey()
{
  if (m_cursorPos > 0)
  {
    int numCharsToSubtractFromLineWidth;
    /*cursorPosChanged =*/
//    if( m_content[m_cursorPos] == '\n')
//      m_cursorLineBeginCharIndex = GetBeginOfWindowLine(m_cursorPos, 
//        numCharsToSubtractFromLineWidth);
    if( m_cursorPos == m_cursorLineBeginCharIndex)
      m_cursorLineBeginCharIndex = GetBeginOfWindowLine(m_cursorPos, 
        numCharsToSubtractFromLineWidth);      
    m_cursorPos--;
    ShowCursorPos();
  }
}


void TextBox::HandleRightArrowKey()
{
//  defdisp = FALSE;
  const int textLength = m_content.length();
  if( m_cursorPos < textLength )
  {
    if( m_content[m_cursorPos] == '\n' )
    {
      m_cursorLineBeginCharIndex = m_cursorPos + 1;
//      m_cursorXpos = 0;
    }
    m_cursorPos ++;
    if(m_cursorPos - m_cursorLineBeginCharIndex == m_lineWidth )
    {
      m_cursorLineBeginCharIndex = m_cursorPos;
//      m_cursorXpos = 0;
    }
    ShowCursorPos();
  }
}

int TextBox::HandleAction(const int ch)
{
  int m_cursor_mode = curses::Cursor::Terminal_specific_normal_mode;
  /** see https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses */
  /*NCURSES_CONST*/ const char * keyName = keyname(ch);
  switch( ch )
  {
  case ERR :
    break;
  case KEY_ESC :
    //std_str = originalString; /* restore original */
//    stop = TRUE;
      //TODO really remove as key listener? why? (give examples))
    RemoveAsKeyListener();
    break;
  case KEY_UP:
    HandleKeyUp();
    break;
  case KEY_DOWN:
    HandleKeyDown(ch);
    break;
  case KEY_NPAGE:
    HandleKeyNextPage();
    break;
  case KEY_PPAGE:
    HandleKeyPreviousPage();
    break;
  case KEY_LEFT:
    HandleLeftArrowKey();
    break;
  case KEY_RIGHT:
    HandleRightArrowKey();
    break;
  default :
    /** Ctrl+right_key */
    if( strcmp("kLFT5", keyName) == 0 )
      HandleCtrlLeftKey();
    /** Ctrl+right_key */
    else if( strcmp("kRIT5", keyName) == 0 )
      HandleCtrlRightKey();
    else if(m_editable)
      return handleEdit(ch, m_cursor_mode);
    else
      return Curses::Window::inputNotHandled;
  }
  return ch;
}



void TextBox::SetFocus(bool focus)
{
  curses::UIcontrol::SetFocus(focus);
  if( focus )
  {
  //  m_hasFocus = focus;
  //  handleInput();
    int cursor_mode = //    insert ? 
  //    Curses::Cursor::Terminal_specific_high_visibility_mode : 
      curses::Cursor::Terminal_specific_normal_mode;
    curs_set(cursor_mode); /** Show cursor (if possible) */
//    int cursorX=0, cursorY=0;
//    if(m_drawBorder)
//    {
//      cursorX=1;
//      cursorY=1;
//    }
//    GetCursorXYfrom1DimensionalPos(cursorX, cursorY);
//    /** https://www.ibm.com/support/knowledgecenter/en/ssw_aix_61/com.ibm.aix.genprogc/control_cursor_wcurses.htm :
//     *  "Moves the logical cursor associated with a user-defined window" */
//    wmove(m_windowHandle, cursorY, cursorX);
    ShowCursorPos();
//    wrefresh(m_windowHandle);
    SetAsKeyListener();
  }
  else
    RemoveAsKeyListener();
}

void TextBox::SetText(const char text [])
{
  m_content = text;
}

fastestUnsignedDataType TextBox::GetCharPosOfBeginOfLine(int lineNumber)
{
  fastestUnsignedDataType charPos = 0;
  if( lineNumber > 0)
  {
    const char * beginOfLine = m_content.c_str();
    const char * const beginOfString = m_content.c_str();
    const char * p_currentChar = m_content.c_str();
    int currentCharPos = 0;
    char currentChar;
    int currentLineNumber = 0;
    for( ; /* *p_currentChar*/ (beginOfString + currentCharPos) != '\0';
         /*p_currentChar++*/ currentCharPos ++ )
    {
      currentChar = *(beginOfString + currentCharPos);
      if( currentChar == '\n' || (beginOfString + currentCharPos - beginOfLine) > m_lineWidth)
      {
        beginOfLine = /*p_currentChar*/ beginOfString + currentCharPos + 1;
        currentLineNumber ++;
        if( lineNumber == currentLineNumber)
        {
          charPos = beginOfLine - beginOfString;
          break;
        }
      }
    }
  }
  return charPos;
}

/** */
void TextBox::ShowWithLineBeginningAtCharPos(fastestUnsignedDataType charPos)
{
//  if( m_drawBorder)
//    m_lineWidth
//    if( m_wrapLines )
//  const char * beginOfLine = m_content.c_str();
  const char * const beginOfString = m_content.c_str();
  const char * p_currentChar = m_content.c_str();
  int currentCharPos = 0;
  char currentChar;
//  int beginOfLineCharIndex = 0;
  int currentLineNumber = 0;
  for( ; /* *p_currentChar*/ currentCharPos < m_content.size();
       /*p_currentChar++*/ currentCharPos ++ )
  {
    //TODO SIGSEGV here when at end of text
    currentChar = *(beginOfString + currentCharPos);
    if( currentChar == '\n' || (/*beginOfString + currentCharPos - beginOfLine*/
        currentCharPos - m_cursorLineBeginCharIndex ) > m_lineWidth)
    {
//      beginOfLine = /*p_currentChar*/ beginOfString + currentCharPos + 1;
      m_cursorLineBeginCharIndex = currentCharPos + 1;
      m_cursorPos = currentCharPos + 1;
      currentLineNumber ++;
    }
    if( currentCharPos >= charPos)
    {
      m_1stLineToShow = currentLineNumber;
      m_1stLineToShowBeginCharIndex = m_cursorLineBeginCharIndex;
#ifdef _DEBUG
      const char * p_beginOfLine = m_content.c_str() + m_cursorLineBeginCharIndex;
#endif
      break;
    }
  }
  show();
}

/** this method only needs to be called if either the text changes or the 
 *  window size changes, */
fastestUnsignedDataType TextBox::getNumberOfLinesNeededForText(
  fastestUnsignedDataType lineWidth)
{
  const int numTextChars = m_content.length();
//  fastestUnsignedDataType numLines = numTextChars / lineWidth;
//  if( numTextChars % lineWidth > 0)
//    numLines++;
  fastestUnsignedDataType numLines = 0;
  const char * const beginOfString = m_content.c_str();
  const char * p_currentChar = m_content.c_str();
  int currentCharPos = 0;
  char currentChar;
  int beginOfLineCharIndex = 0;
  for( ; /* *p_currentChar*/ currentCharPos < numTextChars;
       /*p_currentChar++*/ currentCharPos ++ )
  {
    currentChar = *(beginOfString + currentCharPos);
    if( currentChar == '\n' || (/*beginOfString + currentCharPos - beginOfLine*/
        currentCharPos - beginOfLineCharIndex ) > m_lineWidth)
    {
//      beginOfLine = /*p_currentChar*/ beginOfString + currentCharPos + 1;
      beginOfLineCharIndex = currentCharPos + 1;
      numLines ++;
    }
  }
  if( currentCharPos - beginOfLineCharIndex > 0 )
    numLines ++;
  return numLines;
}

void TextBox::displayScrollBar()
{
  
}

void TextBox::HandleCurrentLine(
//  const std::string & currentLine,
//  const int lineNumber,
//  const int numCharsToPrint
  const HandleCurrentLineParams & handleCurrentLineParams
  )
{
  mvwaddnstr(m_windowHandle,
    handleCurrentLineParams.windowLineNumber + m_drawBorder /** y position*/, 
    m_drawBorder /** x position */, 
    handleCurrentLineParams.p_windowLineBegin /** string */, 
    handleCurrentLineParams.numCharsToPrint /** max number of chars */);
}

void TextBox::show()
{
  int maxy;
  int maxx;
  /** Erase all content from before. */
  wclear(m_windowHandle);
  setcolor(m_windowHandle, m_colorPair);
#ifdef PDCURSES
  maxy = getmaxy(m_windowHandle);
  maxx = getmaxx(m_windowHandle);
#else
  getmaxyx(m_windowHandle, maxy, maxx);
#endif
//  bool drawBorder = true;
  m_numVisibleLinesForText = maxy;
  m_lineWidth = maxx;
  if(m_drawBorder)
  {
    m_numVisibleLinesForText -= 2;
    m_lineWidth -= 2;
  }
  
  const fastestUnsignedDataType numLinesForMaxLineWidth = 
    getNumberOfLinesNeededForText(maxx - m_drawBorder * 2);
  const fastestUnsignedDataType numLinesForLineWidthMinus1 = 
    getNumberOfLinesNeededForText(maxx - 1 - m_drawBorder * 2);
  bool shouldDrawScrollBar = false;
  if( numLinesForMaxLineWidth > m_numVisibleLinesForText)
  {
    shouldDrawScrollBar = true;
    if( !m_drawBorder)
      m_lineWidth = maxx - 1 /** Space needed for vertical scroll bar. */;
  }
  else
    if( !m_drawBorder )
      m_lineWidth = maxx;
  
  HandleCurrentLineParams handleCurrentLineParams;
  handleCurrentLineParams.p_windowLineBegin = m_content.c_str() + 
    //(m_1stLineToShow * m_lineWidth);
    GetCharPosOfBeginOfLine(m_1stLineToShow);
  handleCurrentLineParams.p_textLineBegin = handleCurrentLineParams.p_windowLineBegin;
  const char * const lastChar = m_content.c_str() + m_content.length();
  int currentXpos = 0;
  handleCurrentLineParams.windowLineNumber = 0;
  
  if(m_drawBorder)
    colorBox(m_windowHandle, m_colorPair, 1);
  int numCharsInCurrentWindowLine;
  int numCharsToAdvance;
  int numCharsInCurrentTextLine;
//  std::string currentLine;
  while( handleCurrentLineParams.p_windowLineBegin < lastChar && 
    handleCurrentLineParams.windowLineNumber + m_drawBorder <= 
    m_numVisibleLinesForText )
  {
    const char * p_textLineEnd = strchr(handleCurrentLineParams.p_windowLineBegin, '\n');
    /** No newline found. */
    if( p_textLineEnd == NULL )
      p_textLineEnd = m_content.c_str() + m_content.size();
    handleCurrentLineParams.charIndexOfTextLineEnd = //m_content.find('\n', 
      //handleCurrentLineParams.p_windowLineBegin - m_content.c_str() );
      p_textLineEnd - m_content.c_str();
    if( p_textLineEnd != NULL && handleCurrentLineParams.p_windowLineBegin == 
      handleCurrentLineParams.p_textLineBegin )
      numCharsInCurrentTextLine = p_textLineEnd - 
        handleCurrentLineParams.p_textLineBegin;
    
    numCharsInCurrentWindowLine = p_textLineEnd - handleCurrentLineParams.p_windowLineBegin;
    
//    currentLine = std::string(currentChar, numCharsInCurrentWindowLine);
    /** "<=" because also advance including the newline if a newline ends at 
       line end. (else an additional empty line would be displayed afterwards.*/
    if(numCharsInCurrentWindowLine <= m_lineWidth )
    {
      handleCurrentLineParams.p_textLineBegin = p_textLineEnd + 1;
      numCharsToAdvance = numCharsInCurrentWindowLine + 1;
      /** -> do NOT print newline chars! */
      handleCurrentLineParams.numCharsToPrint = numCharsInCurrentWindowLine;
    }
    else
    {
      numCharsToAdvance = m_lineWidth;
      handleCurrentLineParams.numCharsToPrint = numCharsToAdvance;
    }
    HandleCurrentLine(handleCurrentLineParams);
//    currentXpos += m_lineWidth;
    handleCurrentLineParams.p_windowLineBegin += numCharsToAdvance;
    handleCurrentLineParams.windowLineNumber++;
  }
  if(shouldDrawScrollBar)
    drawScrollBar(m_windowHandle, numLinesForLineWidthMinus1, maxy, 0, maxx - 1);
  ShowCursorPos();
//  wrefresh(m_windowHandle);
}

void TextBox::handleInput()
{
  char * tp;
  int cursor_mode = //    insert ? 
//    Curses::Cursor::Terminal_specific_high_visibility_mode : 
    curses::Cursor::Terminal_specific_normal_mode;
  curs_set(cursor_mode); /** Show cursor (if possible) */

  int currentInput = 0;
  while( ! stop)
  {
//    idle();
    repaintEditbox( /*p_editWindow*/ m_windowHandle, m_cursorPos, m_content.c_str() );
    //TODO using wgetch(...) prevents processing of Curses::EventQueue g_eventQueue
    currentInput = wgetch(/*p_editWindow*/ m_windowHandle);
    switch( currentInput )
    {
    case ERR :
      break;
    case KEY_ESC :
      //std_str = originalString; /* restore original */
      stop = TRUE;
      break;
    case KEY_LEFT:
      if (m_cursorPos > 0)
          m_cursorPos--;
      break;
    case KEY_RIGHT:
      defdisp = FALSE;
      if( m_cursorPos < m_content.length() )
        m_cursorPos ++;
      break;
    }
    if(m_editable)
      handleEdit(currentInput, cursor_mode);
  }
  curs_set(curses::Cursor::Invisible); /* set cursor to invisible */
//  }
//  return currentInput;
}
}//namespace 
