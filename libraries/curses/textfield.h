#pragma once//Include guard.
#include <curses.h> //struct WINDOW

# define EDITBOXCOLOR     (9 | A_BOLD | A_REVERSE)

#include <string>
//namespace std {
//  class string;
//}

enum insertMode { overwriteChar = 0, insertChar };

int editText(WINDOW * win, std::string & std_str, int field);