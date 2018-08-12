#pragma once /** Include guard. */

//#include "Window.hpp"
#include "../windows/WindowHandleWindow.hpp"//base class WindowHandleWindow
#include <libraries/curses/color.h> //A_ATTR
#include <set> //class std::set

namespace curses {
class UIcontrol
  : public curses::WindowHandleWindow
{
protected:
  bool m_hasFocus;
  chtype m_colorPair;
//  static chtype s_deactivateColorPair;
  /** https://linux.die.net/man/3/init_pair : 
   *  "The value of the first argument must be between 1 and COLOR_PAIRS-1" */
  enum colorPairIndices {activated = 1, deactivated};
  /** Use a set to avoid same values inserted multiple times. */
  static std::set<int> s_colorPairIndices;
public:
  UIcontrol() 
    : curses::WindowHandleWindow(true)
    , m_hasFocus(false)
//    , m_deactivateColorPair()
    {}
  static void Init() {
    /** init_pair(...) (ncurses):parameters
     * 1. number of colour pair,
     * 2. foreground colour number,
     * 3. background colour number
     *   "& ~A_ATTR" : remove possible attributes like "A_BOLD" */
    init_pair(activated & ~A_ATTR, COLOR_WHITE, COLOR_BLUE);
    init_pair(deactivated & ~A_ATTR, COLOR_WHITE, COLOR_BLACK);
    s_colorPairIndices.insert(activated);
    s_colorPairIndices.insert(deactivated);
//    s_deactivateColorPair;
  }
  bool HasFocus() const { return m_hasFocus;}
  /** E.g. shows the cursor for controls containing text. */
  virtual void SetFocus(bool focus);
  /** Shows the control (does the output via curses routines) */
  virtual void show() = 0;
};
}
