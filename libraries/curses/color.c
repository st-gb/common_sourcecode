#include <curses.h> //WINDOW, wattrset(...), chtype
#include "color.h" //A_ATTR

/** Source code adapted from PDCurses-3.4/demos/tui.c */

#ifdef __cplusplus
extern "C" {
#endif //#ifdef __cplusplus__
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
#ifdef __cplusplus__
} //extern "C"
#endif //#ifdef __cplusplus__

