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
//    enum alignment { center }
  private:
    enum area m_area;
//    std::vector<curses::WindowHandleWindow *> m_windows;
    /** Use class Window as elements because also non-handle windows should be 
     *  supported. */
    typedef std::map<enum area, Curses::Window *> containerType;
    containerType m_area2WindowContainer;
//    WINDOW * m_windowHandle;
  public:
    BorderLayout(/*enum area area*/ /*WINDOW * windowHandle*/ )
      /*: m_area(area)*/ /*: m_windowHandle(windowHandle)*/ {}
    void add(Curses::Window * p, enum area area 
      /*, enum alignment horizontalAlignment = center*/ )
    {
      m_area2WindowContainer.insert(std::make_pair(area, p) );
    }
    windowsContainerType getDirectlyContainedWindows() const;
    void GetMinimalSize(int & width, int & height);
    void layout();
  };
}
