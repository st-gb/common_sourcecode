#include "TopLevelWindow.hpp"
#include "../LayoutManager/LayoutManagerBase.hpp"

namespace curses {
  int TopLevelWindow::HandleAction(const int ch)
  {
    int ret = -2;
    /** see https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses */
    /*NCURSES_CONST*/ const char * keyName = keyname(ch);
    switch(ch)
    {
      case KEY_RESIZE :
        doLayout();
        break;
      case '\t':
      {
        int i = 2;
        if(mp_layoutManager)
          mp_layoutManager->SetFocusToNextUIcontrol();
      }
        break;
      default:
      {
        ret = Curses::Window::inputNotHandled;
//        char charWithoutCtrl = ctrl('\t');
      }
    }
//    if( consumedInput )
//      wrefresh(windowToShowMenuIn);
    return ret;
  }
}

