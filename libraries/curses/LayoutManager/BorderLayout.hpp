#include "LayoutManagerBase.hpp" //Base class
#include <map> //class std::map
#include <curses.h> //WINDOW *

/** Forwar declarations */
namespace ncurses { class WindowHandleWindow; }

namespace curses {
  class BorderLayout
    : public curses::LayoutManagerBase
  {
  public:
    enum area { top, bottom, left, right, center};
  private:
    enum area m_area;
//    std::vector<curses::WindowHandleWindow *> m_windows;
    typedef std::map<enum area, curses::WindowHandleWindow *> containerType;
    containerType m_area2WindowContainer;
//    WINDOW * m_windowHandle;
  public:
    BorderLayout(/*enum area area*/ /*WINDOW * windowHandle*/ )
      /*: m_area(area)*/ /*: m_windowHandle(windowHandle)*/ {}
    void add(curses::WindowHandleWindow * p, enum area area)
    {
      m_area2WindowContainer.insert(std::make_pair(area, p) );
    }
    std::vector<curses::WindowHandleWindow *> getDirectlyContainedWindows() const;
    void GetMinimalSize(int & width, int & height);
    void layout();
  };
}
