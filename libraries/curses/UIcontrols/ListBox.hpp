#pragma once
//#include "../windows/WindowHandleWindow.hpp"
#include "../UIcontrols/UIcontrol.hpp" //base class curses::UIcontrol
#include <string> //class std::string
#include <hardware/CPU/fastest_data_type.h> //fastestUnsignedDataType

namespace curses {
class ListBox
  : public curses::UIcontrol
{
  chtype m_backGroundColorPair, m_currentSelectionColorPair;
  int m_currentListBoxEntryIndex;
  int m_numberOfListBoxEntries;
  int m_firstListBoxEntryToShow;
  int m_selectionMarkerYpos;
  int m_numberOfLinesForListBoxEntries;
  char * m_title;
  char ** m_listBoxItems;
public:
  ListBox(chtype backGroundColorPair, chtype currentSelectionColorPair)
    : m_currentListBoxEntryIndex(0)
    , m_firstListBoxEntryToShow(0)
    , m_selectionMarkerYpos(0)
    , m_title(NULL)
    , m_listBoxItems(NULL)
    , m_backGroundColorPair(backGroundColorPair)
    , m_currentSelectionColorPair(currentSelectionColorPair)
    {}
  ~ListBox();
  void FreeMemory();
  std::string GetCurrentSelectionString() const;
  int HandleAction(const int ch);
  void HandleKeyDown();
  void HandleKeyUp();
//  void create();
//  void create(const char * listBoxItems [], int numberOfListBoxEntries);
  void SetContent(std::vector<std::string> & );
  void SetCurrentSelection(fastestUnsignedDataType index) { 
    m_currentListBoxEntryIndex = index; }
  void show();
};
}

