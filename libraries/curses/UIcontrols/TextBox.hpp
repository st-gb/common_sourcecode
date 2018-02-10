#pragma once

#include <curses.h> //WINDOW
#include <string> //class std::string:
//#include <libraries/curses/UIcontrols/WindowHandleWindow.hpp>
#include <libraries/curses/UIcontrols/UIcontrol.hpp> //base class UIcontrol

namespace Curses {
class TextBox
  : public //Curses::WindowHandleWindow
      curses::UIcontrol
{
public:
  TextBox(
//    WINDOW * p_superWindow, 
//    WINDOWconst std::string & std_strContent, 
//    int numLines, int numColumns
      chtype colorPair
    );
  ~TextBox();
  void create();
  void create(WINDOW * const p_superWindow, int numLines, int numColumns, 
    int x, int y);
  void displayScrollBar();
  fastestUnsignedDataType getNumberOfLinesNeededForText(fastestUnsignedDataType lineWidth);
  int handleEdit(const int currentInput, int & cursor_mode);
  void handleInput();
  int HandleAction(const int ch);
  void HandleCtrlLeftKey();
  void HandleCtrlRightKey();
  void ShowCursorPos();
  void showText();
  const std::string & getText() const { return m_content;}
  void SetFocus(bool focus);
  void SetText(const char []);
  void SetEditable(bool editable) {m_editable = editable; }
private:
  bool m_editable;
  int m_lineWidth;
  bool m_drawBorder;
  chtype m_colorPair;
  bool stop = FALSE, insertMode = TRUE;
  fastestUnsignedDataType m_cursorPos;
  int numLines, numColumns;
  WINDOW /* * p_editWindow,*/ * m_p_superWindow;
  int m_oldAttribute;
  std::string m_content;
  bool defdisp = TRUE;
};
}
