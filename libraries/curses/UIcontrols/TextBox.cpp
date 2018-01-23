
#include <curses.h> // WINDOW
#include <string> //class std::string
#include <hardware/CPU/fastest_data_type.h>
#include "../textfield.h"
#include "../color.h"
#include <libraries/curses/curs_set_constants.h>
#include "TextBox.hpp"
#include <libraries/curses/UIcontrols/Window.hpp>

/** Following code is from PDCurses-3.4/demos/tui.c, tui.h */
 
#define KEY_ESC    0x1b  /** "Esc" key */
#define KEY_BKSP   0x8   /** "<-" key */

#ifndef PDCURSES
static char wordchar(void)
{
    return 0x17;    /* ^W */ 
}
#endif

static void repaintEditbox(WINDOW *win, int x, const char buffer[] )
{
#ifndef PDCURSES
    int maxy;
#endif
    int maxX;

#ifdef PDCURSES
    maxX = getmaxx(win);
#else
    getmaxyx(win, maxy, maxX);
#endif
    werase(win);
//    mvwprintw(win, 0, 0, "%s", /*padStr(buffer, maxX)*/ buffer );
    mvwaddstr(win, 0, 0, buffer );
    /** https://www.ibm.com/support/knowledgecenter/en/ssw_aix_61/com.ibm.aix.genprogc/control_cursor_wcurses.htm :
     *  "Moves the logical cursor associated with a user-defined window" */
    wmove(win, 0, x);
    wrefresh(win);
}

namespace Curses
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
  )
//  : m_p_superWindow(NULL)//p_superWindow)
//    , p_editWindow(NULL)
   //, m_content(std_strContent)
{
}

void TextBox::create()
{
  
}

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
  /*p_editWindow*/ handle = //subwin( p_superWindow,
    Curses::Window::CreateWindowRelativePos(
    p_superWindow,
    numLines,
    numColumns /* number of colums */, 
    y, //begy + cury,
    x //begx + curx
    );
  //TODO is NULL when (indirectly) called from changePartitionTableOffsets(...)
  if( ! /*p_editWindow*/ handle )
    return;
  m_oldAttribute = /*p_editWindow*/handle->_attrs;
  colorBox( /*p_editWindow*/ handle, EDITBOXCOLOR, 0);

  /** http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/init.html
   *  "enables the reading of function keys like F1, F2, arrow keys etc." */
  keypad( /*p_editWindow*/ handle, TRUE); /** Enable cursor keys */
}

TextBox::~TextBox()
{
  if( /*p_editWindow*/ handle)
  {
    wattrset( /*p_editWindow*/ handle, m_oldAttribute);
  //  repaintEditbox( p_editWindow, bufferPointer - buffer, buffer);
    delwin( /*p_editWindow*/ handle);
    touchwin(m_p_superWindow);
    wrefresh(m_p_superWindow);
  }
}

void TextBox::handleEdit(const int currentInput, int & cursor_mode)
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
      m_content.erase(cursorPos, /** Only erase 1 character. */ 1  );
      break;
    case KEY_BKSP:
    case KEY_BACKSPACE:
      if( cursorPos > 0)
        m_content.erase( -- cursorPos, /** Only erase 1 character. */ 1 );
      break;
    case '\t':            /* TAB -- because insert
                              is broken on HPUX */
    case KEY_IC:          /* enter insert mode */
    case KEY_EIC:         /* exit insert mode */
      defdisp = FALSE;
      insertMode = !insertMode; /**Switch the insert mode*/
      cursor_mode = insertMode ? 
        Curses::Cursor::Terminal_specific_high_visibility_mode : 
        Curses::Cursor::Terminal_specific_normal_mode;
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
        cursorPos = 0;
        m_content.clear();
      }
      else if(currentInput == wordchar() )   /* ^W */
      {
        int charPosAfterWord = cursorPos;
        while( (cursorPos > 0) && ( m_content.at(cursorPos - 1) == ' ') )
          cursorPos --;
        while( (cursorPos > 0) && ( m_content.at(cursorPos - 1) != ' ') )
          cursorPos --;
        /** Remove all characters between cursorPos and charPosAfterWord */
        m_content.erase(cursorPos, charPosAfterWord - cursorPos);
      }
      else if (isprint(currentInput) ) /** If printable character. */
      {
        if (defdisp)
        {
          cursorPos = 0;
          m_content.clear();
          defdisp = FALSE;
        }
        if (insertMode == insertChar )
        {
          if( m_content.length() < numColumns - 1)
          {
            m_content.insert(cursorPos ++, 1, (char) currentInput);
          }
        }
        else if( cursorPos < numColumns - 1)
        {
          if( cursorPos == m_content.size() ) //if cursor is at last char 
              m_content += currentInput; //append character.
          else //Overwrite char
            m_content.at(cursorPos ++) = currentInput;
        }
      }
    }
}

void TextBox::SetText(const char text [])
{
  m_content = text;
}

void TextBox::handleInput()
{
  char * tp;
  int cursor_mode = //    insert ? 
//    Curses::Cursor::Terminal_specific_high_visibility_mode : 
    Curses::Cursor::Terminal_specific_normal_mode;
  curs_set(cursor_mode); /** Show cursor (if possible) */

  int currentInput = 0;
  while( ! stop)
  {
//    idle();
    repaintEditbox( /*p_editWindow*/ handle, cursorPos, m_content.c_str() );
    //TODO using wgetch(...) prevents processing of Curses::EventQueue g_eventQueue
    currentInput = wgetch(/*p_editWindow*/ handle);
    switch( currentInput )
    {
    case ERR :
      break;
    case KEY_ESC :
      //std_str = originalString; /* restore original */
      stop = TRUE;
      break;
    case KEY_LEFT:
      if (cursorPos > 0)
          cursorPos--;
      break;
    case KEY_RIGHT:
      defdisp = FALSE;
      if( cursorPos < m_content.length() )
        cursorPos ++;
      break;
    }
    if(m_editable)
      handleEdit(currentInput, cursor_mode);
  }
  curs_set(Curses::Cursor::Invisible); /* set cursor to invisible */
//  }
//  return currentInput;
}
}//namespace 
