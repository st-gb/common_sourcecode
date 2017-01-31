#pragma once

//#include <curses.h> //WINDOW
struct _win_st;
typedef struct _win_st WINDOW;

namespace Curses
{
//  static eventQueue;

  int GetChar(WINDOW * p_window);
}
