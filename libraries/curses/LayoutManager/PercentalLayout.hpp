#pragma once /** Include guard. */
#include "LayoutManagerBase.hpp" //Base class
#include "../windows/WindowHandleWindow.hpp"
#include <vector> //class std::vector

namespace curses {
  struct WindowHandleWindowAndPercentage
  {
    Curses::WindowHandleWindow * m_p;
    float m_percent;
    WindowHandleWindowAndPercentage(Curses::WindowHandleWindow * p, float percent)
      : m_p(p), m_percent(percent) { }
  };
  /** class that stands for percental (%) layout. e.g. for horizontal direction
      1 area gets 70% of width, the other 30% */
  class PercentalLayout
    : public curses::LayoutManagerBase
  {
  public:
    enum direction { horizontal, vertical};
  private:
    enum direction m_direction;
//    WINDOW * m_windowHandle;
    std::vector<curses::WindowHandleWindowAndPercentage> m_windows;
  public:
    PercentalLayout(/*WINDOW * windowHandle,*/ enum direction dir)
      : m_direction(dir) /*, m_windowHandle(windowHandle)*/ {}
    void add(Curses::WindowHandleWindow * p, float percent)
    {
      m_windows.push_back(WindowHandleWindowAndPercentage(p, percent));
    }
    std::vector<Curses::WindowHandleWindow *> getDirectlyContainedWindows() const;
    void layout();
  };
}
