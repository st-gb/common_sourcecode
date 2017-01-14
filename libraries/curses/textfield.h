#pragma once

//from PDcurses demo: tui.h
#ifdef A_COLOR
#define A_ATTR  (A_ATTRIBUTES ^ A_COLOR)  /* A_BLINK, A_REVERSE, A_BOLD */
#else
#define A_ATTR  (A_ATTRIBUTES)            /* standard UNIX attributes */
#endif

# define EDITBOXCOLOR     (9 | A_BOLD | A_REVERSE)

#include <string>
//namespace std {
//  class string;
//}

int editText(WINDOW *win, std::string & std_str, int field);
void colorBox(WINDOW * win, chtype color, int hasbox);