#pragma once //Include guard.

/** Source code adapted from PDCurses-3.4/demos/tui.h */

#ifdef A_COLOR
#define A_ATTR  (A_ATTRIBUTES ^ A_COLOR)  /* A_BLINK, A_REVERSE, A_BOLD */
#else
#define A_ATTR  (A_ATTRIBUTES)            /* standard UNIX attributes */
#endif

#ifdef __cplusplus
extern "C" {
#endif //ifdef __cplusplus__
/*static*/ void setcolor(WINDOW * win, chtype color);
/*static*/ void colorBox(WINDOW * win, chtype color, int hasbox);
#ifdef __cplusplus
}//extern "C"
#endif //#ifdef __cplusplus__

