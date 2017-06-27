#include <curses.h> //WINDOW, wattrset(...), chtype
#include "color.h" //A_ATTR

/** Source code adapted from PDCurses-3.4/demos/tui.c */

#ifdef __cplusplus
extern "C" {
#endif //#ifdef __cplusplus__
  
/** Only sets the color for the printed text.*/
/*static*/ void setcolor(WINDOW * win, chtype color)
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

/** Sets the color for the WHOLE window, not just for the text printed as 
 *  setcolor(...) only does. */
/*static*/ void colorBox(WINDOW * windowToSetColourTo, chtype color, int drawBox)
{
  chtype attr = color & A_ATTR;  /* extract Bold, Reverse, Blink bits */
  setcolor(windowToSetColourTo, color);
#ifdef A_COLOR
  if( has_colors() )
    wbkgd(windowToSetColourTo, COLOR_PAIR(color & A_CHARTEXT) | (attr & ~A_REVERSE));
  else
#endif
    wbkgd(windowToSetColourTo, attr);
  /** Is needed to clear/erase the whole window. */
  werase(windowToSetColourTo);
  
  if( drawBox )
  {
    int maxy;
#ifndef PDCURSES
    int maxx;
#endif
#ifdef PDCURSES
    maxy = getmaxy(windowToSetColourTo);
#else
    getmaxyx(windowToSetColourTo, maxy, maxx);
#endif
    if( maxy > 2 )
      box(windowToSetColourTo, 0, 0);
  }
  touchwin(windowToSetColourTo);
  wrefresh(windowToSetColourTo);
}
#ifdef __cplusplus__
} //extern "C"
#endif //#ifdef __cplusplus__

