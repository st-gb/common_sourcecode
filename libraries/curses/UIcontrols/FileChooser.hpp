#include <curses.h> //WINDOW
#include <string> //class std::string

std::string GetDirToGetContentsFrom(const char * const initialFileOrDir);

std::string ChooseFile(
  const char * const initialDir, 
  WINDOW * pWindowToShowFileChooserIn,
  chtype backGroundColorPair, 
  chtype currentSelectionColorPair
);
