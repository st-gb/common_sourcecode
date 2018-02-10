#include <curses.h> //WINDOW

void drawScrollBar(
  WINDOW * inputWindow, 
  int numberOfListBoxEntries, 
  int numberOfLinesForListBoxEntries,
  int firstListBoxEntryToShow, 
  int horizontalIndexForScrollBar)
{
  float p = 1.0f;
  if( numberOfListBoxEntries > numberOfLinesForListBoxEntries)
    p = (float) numberOfLinesForListBoxEntries / numberOfListBoxEntries;
  int numberOfThumbLines = numberOfLinesForListBoxEntries * p;
  if( numberOfThumbLines == 0 )
    numberOfThumbLines = 1;
  
  int lastScrollBarThumbLine;
  int firstIndex;
  if( numberOfListBoxEntries - firstListBoxEntryToShow == 
      numberOfLinesForListBoxEntries )
  {
    firstIndex = numberOfLinesForListBoxEntries - numberOfThumbLines;
  }
  else
  {
    const float firstEntryDivByNumEntries = (float) firstListBoxEntryToShow / 
      numberOfListBoxEntries;
    firstIndex = (float) (firstEntryDivByNumEntries
      * numberOfLinesForListBoxEntries);
  }
  lastScrollBarThumbLine = numberOfThumbLines + firstIndex + 1;
  for(int index = firstIndex + 1; index < lastScrollBarThumbLine; index ++)
  {
    //https://stackoverflow.com/questions/6617419/add-a-scrollbar-on-ncurses-or-make-it-like-more
//    mvwprintw(inputWindow, index, 0, "%c", 30);
//    mvwaddch(inputWindow, index, 0, 30);
    //http://melvilletheatre.com/articles/ncurses-extended-characters/index.html
    mvwaddch(inputWindow, index, horizontalIndexForScrollBar, ACS_CKBOARD);
  }
#ifdef _DEBUG
  wrefresh(inputWindow);
#endif
}

