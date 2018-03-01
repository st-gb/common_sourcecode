/** File:   CurorPosChangedListener.hpp
 * Author: sg
 *
 * Created on 6. Februar 2018, 17:40  */

#ifndef CURSORPOSCHANGEDLISTENER_HPP
#define CURSORPOSCHANGEDLISTENER_HPP

/** Fwd. decl. */
namespace ncurses { class TextBox; }

namespace curses
{
class CursorPosChangedListener {
protected:
  ncurses::TextBox * m_pTextBox;
public:
    CursorPosChangedListener();
    virtual ~CursorPosChangedListener();
    void SetTextBox(ncurses::TextBox * pTextBox) { m_pTextBox = pTextBox;}
    /** Implement functionality in subclasses(!) */
    virtual void Notify() = 0;
};
}

#endif /* CURSORPOSCHANGEDLISTENER_HPP */

