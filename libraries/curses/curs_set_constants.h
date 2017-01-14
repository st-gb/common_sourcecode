#pragma once /** Include guard. */

#include <curses.h> //curs_set(...)
//#define 

namespace Curses
{
  class Cursor
  {
    public:
    /** From http://pubs.opengroup.org/onlinepubs/007908775/xcurses/curs_set.html */
    enum curs_set_constants { 
      Invisible = 0,
      Terminal_specific_normal_mode = 1,
      Terminal_specific_high_visibility_mode = 2 };
    static void SetCursorMode_inline(const enum curs_set_constants mode ) {
      if( curs_set(mode) == ERR )
      {
        if( mode == Terminal_specific_high_visibility_mode )
          //fallback mode
          curs_set(Terminal_specific_normal_mode);
      }
    }
  };
};
