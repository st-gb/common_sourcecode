#pragma once

#include <curses.h> //WINDOW
#include <string> //class std::string:
//#include <libraries/curses/UIcontrols/WindowHandleWindow.hpp>
#include <libraries/curses/UIcontrols/UIcontrol.hpp> //base class UIcontrol
#include <hardware/CPU/fastest_data_type.h>
#include "CursorPosChangedListener.hpp" //class curses::CurorPosChangedListener

/** Fwd. decl. */
namespace curses { class CursorPosChangedListener; }

namespace curses {
class TextBox
  : public //Curses::WindowHandleWindow
      curses::UIcontrol
{
public:
    enum style { no=1, highlightToken=no*2 };
  struct HandleCurrentLineParams
  {
    const char * p_textLineBegin;  
    const char * p_windowLineBegin;
    int windowLineNumber;
    int numCharsToPrint;
    int charIndexOfTextLineEnd;
  };
  TextBox(
//    WINDOW * p_superWindow, 
//    WINDOWconst std::string & std_strContent, 
//    int numLines, int numColumns
      chtype colorPair
    );
  ~TextBox();
  void AddCursorPosChangedListener(
    curses::CursorPosChangedListener * p_cursorPosChangedListener);
//  void create();
  void create(WINDOW * const p_superWindow, int numLines, int numColumns, 
    int x, int y);
  using WindowHandleWindow::create;
  void displayScrollBar();
  int GetBeginOfWindowLine(int currentCharPos, int &);
  fastestUnsignedDataType GetCharPosOfBeginOfLine(int lineNumber);
  fastestUnsignedDataType GetCursorPos() const { return m_cursorPos; }
  fastestUnsignedDataType getNumberOfLinesNeededForText(fastestUnsignedDataType lineWidth);
  void GetMinimalSize(int & width, int & height);
  int GetLastVisibleWindowLineEndCharIndex();
  
  /** Input character handling. */
  int handleEdit(const int currentInput, int & cursor_mode);
  void handleInput();
  int HandleAction(const int ch);
  void HandleCtrlLeftKey();
  void HandleCtrlRightKey();
  virtual void HandleCurrentLine(
//    const std::string & currentLine,
//    const int lineNumber,
//    const int numCharsToPrint
    const HandleCurrentLineParams & handleCurrentLineParams
    );
  void HandleKeyDown(const int ch);
  void HandleKeyUp();
  void HandleLeftArrowKey();
  void HandleRightArrowKey();
  void HandleKeyPreviousPage();
  void HandleKeyNextPage();
  
  void NotifyCursorPosChangedListener();
  void ShowCursorPos();
  void show();
  const std::string & getText() const { return m_content;}
  void SetDrawBorder(bool drawBorder) { m_drawBorder = drawBorder; }
  void SetFocus(bool focus);
  void SetText(const char []);
  void SetEditable(bool editable) {m_editable = editable; }
  void ShowWithLineBeginningAtCharPos(fastestUnsignedDataType);
protected:
  chtype m_colorPair;
  /** char index of the line that contains the cursor. */
  int m_cursorLineBeginCharIndex;
  int m_1stLineToShowBeginCharIndex;
  std::string m_content;
  typedef std::vector<curses::CursorPosChangedListener *> 
    CursorPosChangedListenerContainerType;
  CursorPosChangedListenerContainerType m_cursorPosChangedListenerContainer;
  bool m_drawBorder;
private:
  bool m_editable;
  int m_lineWidth;
  fastestUnsignedDataType m_1stLineToShow;
  fastestUnsignedDataType m_numVisibleLinesForText;
//  chtype m_colorPair;
  bool stop = FALSE, insertMode = TRUE;
  fastestUnsignedDataType m_cursorPos;
  int numLines, numColumns;
  WINDOW /* * p_editWindow,*/ * m_p_superWindow;
  int m_oldAttribute;
  bool defdisp = TRUE;
};
}
