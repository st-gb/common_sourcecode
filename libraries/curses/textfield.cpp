
#include <curses.h> // WINDOW
#include <string> //class std::string
#include <hardware/CPU/fastest_data_type.h>
#include "textfield.h"
#include <libraries/curses/curs_set_constants.h>

/** Following code is from PDcurses demo, tui.c */
 
#define KEY_ESC    0x1b     /* Escape */
#define KEY_BKSP   0x8     /* Escape */

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

/*static*/ void setcolor(WINDOW *win, chtype color)
{
    chtype attr = color & A_ATTR;  /* extract Bold, Reverse, Blink bits */

#ifdef A_COLOR
    attr &= ~A_REVERSE;  /* ignore reverse, use colors instead! */
    wattrset(win, COLOR_PAIR(color & A_CHARTEXT) | attr);
#else
    attr &= ~A_BOLD;     /* ignore bold, gives messy display on HP-UX */
    wattrset(win, attr);
#endif
}
           
/*static*/ void colorBox(WINDOW * win, chtype color, int hasbox)
{
    int maxy;
#ifndef PDCURSES
    int maxx;
#endif
    chtype attr = color & A_ATTR;  /* extract Bold, Reverse, Blink bits */
    setcolor(win, color);
#ifdef A_COLOR
    if (has_colors())
        wbkgd(win, COLOR_PAIR(color & A_CHARTEXT) | (attr & ~A_REVERSE));
    else
#endif
    wbkgd(win, attr);
    werase(win);
#ifdef PDCURSES
    maxy = getmaxy(win);
#else
    getmaxyx(win, maxy, maxx);
#endif
    if (hasbox && (maxy > 2))
        box(win, 0, 0);
    touchwin(win);
    wrefresh(win);
}

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
int editText(WINDOW * p_superWindow, std::string & std_str, int numChars)
{
  std::string originalString;
  char * tp;
  bool defdisp = TRUE, stop = FALSE, insert = TRUE;
  int cury, curx, begy, begx, oldAttribute;
  WINDOW * p_editWindow;
  int currentInput = 0;

//  if ((numChars >= MAXSTRLEN) || (buffer == NULL) ||
//      ((int)strlen(buffer) > numChars - 1))
//      return ERR;

  originalString = std_str;

  /** http://pubs.opengroup.org/onlinepubs/7908799/xcurses/doupdate.html
  * "refresh the current or specified window." */
  wrefresh(p_superWindow);
  getyx(p_superWindow, cury, curx);
  getbegyx(p_superWindow, begy, begx);
  p_editWindow = subwin(p_superWindow, 1, numChars /* number of colums */, begy + cury,
    begx + curx);
  //TODO is NULL when (indirectly) called from changePartitionTableOffsets(...)
  if( ! p_editWindow )
    return 1;
    oldAttribute =  p_editWindow->_attrs;
  colorBox( p_editWindow, EDITBOXCOLOR, 0);

  /** http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/init.html
   *  "enables the reading of function keys like F1, F2, arrow keys etc." */
  keypad( p_editWindow, TRUE); /** Enable cursor keys */

  int cursor_mode = //    insert ? 
//    Curses::Cursor::Terminal_specific_high_visibility_mode : 
//    Curses::Cursor::Terminal_specific_normal_mode ; 
    Curses::Cursor::Terminal_specific_normal_mode;
  curs_set(cursor_mode); /** Show cursor (if possible) */

  const char eraseCharacter = erasechar(); /** curses function */
  const char killCharacter = killchar(); /** curses function */
  fastestUnsignedDataType cursorPos = 0;
  while( ! stop)
  {
//    idle();
    repaintEditbox( p_editWindow, cursorPos, std_str.c_str() );
    currentInput = wgetch(p_editWindow);
    switch( currentInput )
    {
    case ERR :
      break;
    case KEY_ESC :
      std_str = originalString; /* restore original */
      stop = TRUE;
      break;
    case '\n':
//    case KEY_UP:
//    case KEY_DOWN:
        stop = TRUE;
        break;
    case KEY_DC: //Delete Character
//      if (bufferPointer - buffer < strlen(buffer) )
      {
//        memmove((void *)(bufferPointer), (const void *)(bufferPointer + 1),
//          strlen(bufferPointer) );
        std_str.erase(cursorPos, /** Only erase 1 character. */ 1  );
      }
      break;
    case KEY_BKSP:
    case KEY_BACKSPACE:
      if( cursorPos > 0)
        std_str.erase( -- cursorPos, /** Only erase 1 character. */ 1 );
      break;
    case KEY_LEFT:
      if (cursorPos > 0)
          cursorPos--;
      break;
    case KEY_RIGHT:
      defdisp = FALSE;
      if( cursorPos < std_str.length() )
        cursorPos ++;
      break;
    case '\t':            /* TAB -- because insert
                              is broken on HPUX */
    case KEY_IC:          /* enter insert mode */
    case KEY_EIC:         /* exit insert mode */
      defdisp = FALSE;
      insert = !insert;
      curs_set(insert ? 2 : 1); /**set the cursor mode */
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
        std_str.clear();
      }
      else if(currentInput == wordchar() )   /* ^W */
      {
//        tp = bufferPointer;
        int charPosAfterWord = cursorPos;
        while( (cursorPos > 0) && ( std_str.at(cursorPos - 1) == ' ') )
          cursorPos --;
        while( (cursorPos > 0) && ( std_str.at(cursorPos - 1) != ' ') )
          cursorPos --;
        /** Remove all characters between cursorPos and charPosAfterWord */
        std_str.erase(cursorPos, charPosAfterWord - cursorPos);
      }
      else if (isprint(currentInput) )
      {
        if (defdisp)
        {
          cursorPos = 0;
          std_str.clear();
          defdisp = FALSE;
        }
        if (insert)
        {
          if( std_str.length() < numChars - 1)
          {
//            memmove((void *)(bufferPointer + 1), (const void *)bufferPointer,
//                    strlen(bufferPointer) + 1);
            std_str.insert(cursorPos ++, 1, (char) currentInput);
//            *bufferPointer++ = currentInput;
          }
        }
        else if( cursorPos < numChars - 1)
        {
          /* append new string terminator */
          if( cursorPos == std_str.size() ) //if terminating char at pointer
              std_str += currentInput;
          else
            std_str.at(cursorPos ++) = currentInput;
        }
      }
    }
  }
  curs_set(0); /* set cursor to Invisible */
  wattrset( p_editWindow, oldAttribute);
//  repaintEditbox( p_editWindow, bufferPointer - buffer, buffer);
  delwin( p_editWindow);
//  }
  return currentInput;
}

