#pragma once //include guard
#include "../windows/WindowHandleWindow.hpp" //class WindowHandleWindow
#include "TopLevelWindow.hpp" //class TopLevelWindow
#include <string> //class std::string
#include <OperatingSystem/multithread/nativeEvent_type.hpp>

namespace curses {
class FileChooserDialog
  : public curses::TopLevelWindow
{
public:
  enum mode { save, open};
  FileChooserDialog(chtype backGroundColorPair, chtype currentSelectionColorPair)
    : m_backGroundColorPair(backGroundColorPair), 
      m_currentSelectionColorPair(currentSelectionColorPair) {}
    
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

