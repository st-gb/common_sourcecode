#pragma once
#include "../windows/WindowHandleWindow.hpp"

namespace curses {
class ListBox
  : public ncurses::WindowHandleWindow
{
  int m_currentListBoxEntryIndex;
  int m_numberOfListBoxEntries;
  int m_firstListBoxEntryToShow;
  int m_selectionMarkerYpos;
  int m_numberOfLinesForListBoxEntries;
  char * m_title;
  char ** m_listBoxItems;
public:
  ListBox();
  ~ListBox();
  int HandleAction(const int ch);
  void create(char * listBoxItems [], int numberOfListBoxEntries);
};
}

