#include <curses.h>///SCREEN
#include <iostream>///std::cout

namespace curses
{
  SCREEN * GetScreen()
  {
  /** see https://bbs.archlinux.org/viewtopic.php?id=94780 */
  std::cout << "in Linux/Unix the environment variable \"TERM\" must be set "
    "in order for initscr() to succeed.\nSet it e.g. to \"xterm\"" << std::endl ;
  /** http://pubs.opengroup.org/onlinepubs/007908775/xcurses/initscr.html :
   *  "Upon successful completion, initscr() returns a pointer to stdscr. 
   *   Otherwise, it does not return." */
//  WINDOW * p_stdScrWin = initscr();
  /** http://pubs.opengroup.org/onlinepubs/7908799/xcurses/initscr.html
      "The initscr() function is equivalent to:" */
  const char * const environmentVarName = "TERM";
  char * env = getenv(environmentVarName);
  if( env == NULL)
    std::cout << "environment variable \"" << environmentVarName 
      << "\" is not set!->no curses application possible" << std::endl ;
  SCREEN * p_screen = newterm(env, stdout, stdin);
  return p_screen;
  }
}
