#include <curses.h> //WINDOW

#ifdef __cplusplus
extern "C" {
#endif //#ifdef __cplusplus__

unsigned int listBox(
  const char * const listBoxItems [], 
  const char title [],
  WINDOW *,
  chtype backGroundColorPair, 
  chtype currentSelectionColorPair
  );

void HandleKeyDown(
  WINDOW * inputWindow,
  const char * const listBoxItems[],
  const char title[],
  int * p_currentListBoxEntryIndex,
  const int numberOfListBoxEntries,
  int * p_firstListBoxEntryToShow,
  const int numberOfLinesForListBoxEntries,
  int selectionMarkerYpos
  );

void HandleKeyUp(
  WINDOW * inputWindow,
  const char * const listBoxItems[],
  const char title[],
  int * p_currentListBoxEntryIndex,
  const int numberOfListBoxEntries,
  int * p_firstListBoxEntryToShow,
  const int numberOfLinesForListBoxEntries,
  int selectionMarkerYpos
  );

#ifdef __cplusplus
}
#endif //#ifdef __cplusplus__
