#pragma once //include guard
#include "../windows/WindowHandleWindow.hpp" //class WindowHandleWindow
#include "TopLevelWindow.hpp" //class TopLevelWindow
#include <string> //class std::string
#include <OperatingSystem/multithread/nativeEvent_type.hpp>
#include "../UIcontrols/ListBox.hpp"
#include "../UIcontrols/Label.hpp"

namespace curses {
class FileChooserDialog
  : public curses::TopLevelWindow
{
  curses::ListBox * m_p_listBox;
  curses::Label * m_p_folderLabel;
  std::string m_dirToGetContentsFrom;
public:
  enum mode { save, open};
  FileChooserDialog(chtype backGroundColorPair, chtype currentSelectionColorPair)
    : m_backGroundColorPair(backGroundColorPair), 
      m_currentSelectionColorPair(currentSelectionColorPair),
      m_p_listBox(0),
      m_p_folderLabel(0)
      {}
    
    std::string ChooseFile(
      const char * const initialDir, 
      WINDOW * pWindowToShowFileChooserIn,
      enum FileChooserDialog::mode mode);
    int HandleAction(const int ch);
  nativeEvent_type m_closeEvent;
protected:
  chtype m_backGroundColorPair, m_currentSelectionColorPair;
};
}

