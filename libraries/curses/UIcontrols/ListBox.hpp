#pragma once
#include "../windows/WindowHandleWindow.hpp"

namespace curses {
class ListBox
  : public ncurses::WindowHandleWindow
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
  int HandleAction(const int ch);
  void HandleKeyDown();
  void HandleKeyUp();
  void create(const char * listBoxItems [], int numberOfListBoxEntries);
  void show();
};
}

