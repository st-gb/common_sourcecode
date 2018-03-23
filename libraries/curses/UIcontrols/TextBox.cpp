
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

namespace ncurses
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
    m_numVisibleLinesForText(0)
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
    delwin( /*p_editWindow*/ m_windowHandle);
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
        ncurses::Cursor::Terminal_specific_high_visibility_mode : 
        ncurses::Cursor::Terminal_specific_normal_mode;
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
  const int lineWidth = m_drawBorder ? maxx - 2 : maxx; 
  int cursorY = (m_cursorPos - m_lineWidth * m_1stLineToShow) / lineWidth;
  int cursorX = m_cursorPos % lineWidth;
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

void TextBox::HandleKeyUp()
{
  if (m_cursorPos >= m_lineWidth)
  {
    m_cursorPos -= m_lineWidth;
    NotifyCursorPosChangedListener();
    if (m_cursorPos < (m_1stLineToShow * m_lineWidth) )
    {
      m_1stLineToShow--;
      show();
    }  
    ShowCursorPos();
  }
}
    
void TextBox::HandleKeyDown(const int ch)
{
  const int textLength = m_content.length();
  /** If at least 1 line left after cursor position. */
  if(textLength > m_lineWidth && m_cursorPos < textLength - m_lineWidth)
  {
    m_cursorPos += m_lineWidth;
    NotifyCursorPosChangedListener();
    if( m_cursorPos >= ( m_1stLineToShow + m_numVisibleLinesForText) * m_lineWidth )
    {
      m_1stLineToShow++;
      show();
    }
    ShowCursorPos();
  }
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
    
int TextBox::HandleAction(const int ch)
{
  int m_cursor_mode = ncurses::Cursor::Terminal_specific_normal_mode;
  /** see https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses */
  /*NCURSES_CONST*/ const char * keyName = keyname(ch);
  switch( ch )
  {
  case ERR :
    break;
  case KEY_ESC :
    //std_str = originalString; /* restore original */
//    stop = TRUE;
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
    if (m_cursorPos > 0)
    {
      m_cursorPos--;
      ShowCursorPos();
    }
    break;
  case KEY_RIGHT:
    defdisp = FALSE;
    {
      const int textLength = m_content.length();
      if( m_cursorPos < textLength )
      {
        m_cursorPos ++;
        ShowCursorPos();
      }
    }
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
      ncurses::Cursor::Terminal_specific_normal_mode;
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

void TextBox::ShowWithLineBeginningAtCharPos(fastestUnsignedDataType charPos)
{
//  if( m_drawBorder)
//    m_lineWidth
//    if( m_wrapLines )
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
    }
    if( currentCharPos >= charPos)
    {
      m_1stLineToShow = currentLineNumber;
      break;
    }
  }
  show();
}

fastestUnsignedDataType TextBox::getNumberOfLinesNeededForText(
  fastestUnsignedDataType lineWidth)
{
  const int numTextChars = m_content.length();
  fastestUnsignedDataType numLines = numTextChars / lineWidth;
  if( numTextChars % lineWidth > 0)
    numLines++;
  return numLines;
}

void TextBox::displayScrollBar()
{
  
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
  
  const char * currentChar = m_content.c_str() + //(m_1stLineToShow * m_lineWidth);
    GetCharPosOfBeginOfLine(m_1stLineToShow);
  const char * const lastChar = m_content.c_str() + m_content.length();
  int currentXpos = 0, lineNumber = 0;
  
  if(m_drawBorder)
    colorBox(m_windowHandle, m_colorPair, 1);
  int numCharsInCurrentLine;
  int numCharsToAdvance;
  int numCharsToPrint;
  while( currentChar < lastChar && lineNumber + m_drawBorder <= 
    m_numVisibleLinesForText )
  {
    numCharsInCurrentLine = strchr(currentChar, '\n') - currentChar;
    /** "<=" because also advance including the newline if a newline ends at 
       line end. (else an additional empty line would be displayed afterwards.*/
    if(numCharsInCurrentLine <= m_lineWidth )
    {
      numCharsToAdvance = numCharsInCurrentLine + 1;
      /** -> do NOT print newline chars! */
      numCharsToPrint = numCharsInCurrentLine;
    }
    else
    {
      numCharsToAdvance = m_lineWidth;
      numCharsToPrint = numCharsToAdvance;
    }
    mvwaddnstr(m_windowHandle, lineNumber + m_drawBorder /** y position*/, 
      m_drawBorder /** x position */, currentChar /** string */, 
      numCharsToPrint /** max number of chars */);
//    currentXpos += m_lineWidth;
    currentChar += numCharsToAdvance;
    lineNumber++;
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
    ncurses::Cursor::Terminal_specific_normal_mode;
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
  curs_set(ncurses::Cursor::Invisible); /* set cursor to invisible */
//  }
//  return currentInput;
}
}//namespace 
