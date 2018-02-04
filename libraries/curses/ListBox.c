#include <curses.h> //WINDOW
#include <limits.h> //UINT_MAX
#include <string.h> //strlen(...)
#include "UIcontrols/drawScrollBar.h"

void outputDirEntriesList(
  unsigned firstIndex, 
  const char * const listBoxItems [], 
  const unsigned numberOfDirectoryEntries,
//  const unsigned numberOfLinesForInputBox,
  const char title [],  
  WINDOW * inputWindow
  )
{
  wclear(inputWindow);
  mvwprintw(inputWindow, 0, 0, "%s", title);
  for(unsigned currentDirEntryIndex = firstIndex; 
    currentDirEntryIndex < numberOfDirectoryEntries;
    currentDirEntryIndex++)
    mvwprintw(inputWindow, 
      currentDirEntryIndex - firstIndex + 1, 
      3, "%s", listBoxItems[currentDirEntryIndex]);
//  touchwin(inputWindow);
//  wrefresh(inputWindow);
}

//TODO
/** @param listBoxItems: last element must be NULL
 *  @return selected index or UINT_MAX if ESC was pressed */
unsigned int listBox(
  const char * const listBoxItems[]/*, int field*/, 
  const char title [], 
  WINDOW * pBodyWindow)
{
  WINDOW * inputWindow;
  int oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow;
  int bodyWindowMaxY, bodyWindowMaxX;
  int numberOfLinesForInputBox, numberOfColumnsForInputBox, currentListBoxEntryIndex,
    currentDescStringLength,
    maxFieldDescInChars = 0;
  int numberOfListBoxEntries;
  int c = 0;
  bool stop = FALSE;

  for (numberOfListBoxEntries = 0; /** last element has to be NULL */
    listBoxItems[numberOfListBoxEntries] &&
    (currentDescStringLength = strlen(listBoxItems[numberOfListBoxEntries]) ) > 0;
    numberOfListBoxEntries++)
  {
    if( currentDescStringLength > maxFieldDescInChars)
      maxFieldDescInChars = currentDescStringLength;
  }

  const unsigned titleLenghtInChars = strlen(title);

  /** numberOfInputWindows ^= number of fields now */
  numberOfLinesForInputBox = numberOfListBoxEntries + 2;
  numberOfColumnsForInputBox = titleLenghtInChars > maxFieldDescInChars + 4 ?
      titleLenghtInChars : maxFieldDescInChars /*+ field*/ + 4;

  /** Get current cursor x&y position of the body window "curses" function */
  getyx(pBodyWindow, oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow);
  getmaxyx(pBodyWindow, bodyWindowMaxY, bodyWindowMaxX); /* "curses" function */

  if( numberOfLinesForInputBox > bodyWindowMaxY - 1)
      numberOfLinesForInputBox = bodyWindowMaxY - 1;
  if( numberOfColumnsForInputBox > bodyWindowMaxX - 1)
      numberOfColumnsForInputBox = bodyWindowMaxX - 1;
#ifdef PDCURSES
  /** Place input window in center of body window. */
  const unsigned verticalCenter = (bodyWindowMaxY - numberOfLinesForInputBox) / 2;
  const unsigned horizontalCenter = (bodyWindowMaxX - numberOfColumnsForInputBox) / 2;
  inputWindow = mvwinputbox(
    pBodyWindow,
    verticalCenter, horizontalCenter,
    numberOfLinesForInputBox, numberOfColumnsForInputBox);
#elif defined(CURSES)
//  int res = wmove(pBodyWindow, verticalCenter, horizontalCenter);
//  if( res != ERR)
    inputWindow = /*subwin*/derwin(
      pBodyWindow,
      numberOfLinesForInputBox, numberOfColumnsForInputBox,
      0, 0);
#endif

  if( ! inputWindow)
    return 0;
    
  /** http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/init.html
   *  "enables the reading of function keys like F1, F2, arrow keys etc." */
  keypad( inputWindow, TRUE);

  mvwprintw(inputWindow, 0, 0, "%s", title);

  outputDirEntriesList(0, listBoxItems, numberOfListBoxEntries, 
    title, inputWindow);

  const int selectionMarkerYpos = 2;
  mvwprintw(inputWindow, 1, selectionMarkerYpos, "%c", 'x');
  
  const unsigned numberOfLinesForListBoxEntries = numberOfLinesForInputBox - 1;

  currentListBoxEntryIndex = 0;
//    unsigned selectionIndex;
  unsigned firstListBoxEntryToShow = 0;
  drawScrollBar(inputWindow, numberOfListBoxEntries, 
    numberOfLinesForListBoxEntries, firstListBoxEntryToShow, 1);
  while (!stop)
  {
    c = wgetch(inputWindow);
    switch (c)
    {
    case ERR: /** Nothing typed. */
      break;
    case KEY_UP:
//      currentDirEntryIndex = (currentDirEntryIndex + numberOfDirectoryEntries 
//        - 1) % numberOfDirectoryEntries;
      if( currentListBoxEntryIndex > 0)
      {
        currentListBoxEntryIndex --;
      if( currentListBoxEntryIndex < firstListBoxEntryToShow )
      {
        outputDirEntriesList(--firstListBoxEntryToShow, listBoxItems,
          numberOfListBoxEntries, title, inputWindow);
        mvwprintw(inputWindow, 1, selectionMarkerYpos, "%c", 'x');
        //https://stackoverflow.com/questions/6617419/add-a-scrollbar-on-ncurses-or-make-it-like-more
//        mvwprintw(, 1, 0, "%c", 0x25B2);
        drawScrollBar(inputWindow, numberOfListBoxEntries, 
          numberOfLinesForListBoxEntries, firstListBoxEntryToShow, 1);
      }
      else
        if( numberOfListBoxEntries > 0) /** Prevent division by 0. */
        {
          const int lineNumber = currentListBoxEntryIndex - firstListBoxEntryToShow + 1;
          /** Erase previous selection */
          mvwprintw(inputWindow, lineNumber + 1, selectionMarkerYpos, "%c", ' ');
          mvwprintw(inputWindow, lineNumber, selectionMarkerYpos, "%c", 'x');
        }
      }
      break;
    case '\t':
    case KEY_DOWN:
//      if( currentDirEntryIndex == numberOfDirectoryEntries - 1)
//        currentDirEntryIndex = 0;
//      else
//        ++currentDirEntryIndex;
      if( currentListBoxEntryIndex + 1 < numberOfListBoxEntries)
      {
          currentListBoxEntryIndex++;
      if( currentListBoxEntryIndex - firstListBoxEntryToShow + 1 > numberOfLinesForListBoxEntries )
      {
//        firstDirEntryToShow = currentDirEntryIndex - 
//          numberOfLinesForDirEntries + 1;
        firstListBoxEntryToShow++;
        outputDirEntriesList(firstListBoxEntryToShow, listBoxItems, 
          numberOfListBoxEntries, title, inputWindow);
//        wrefresh(pBodyWindow);
        mvwprintw(inputWindow, numberOfLinesForListBoxEntries, selectionMarkerYpos, "%c", 'x');
        drawScrollBar(inputWindow, numberOfListBoxEntries, 
          numberOfLinesForListBoxEntries, firstListBoxEntryToShow, 1);
      }
      else
      {
          const int lineNumber = currentListBoxEntryIndex - firstListBoxEntryToShow;
        /** Erase previous selection */
        mvwprintw(inputWindow, lineNumber, selectionMarkerYpos, "%c", ' ');
        /** Show current selection */
        mvwprintw(inputWindow, lineNumber + 1, selectionMarkerYpos, "%c", 'x');
      }
      }
      break;
//      stop = TRUE;
//      currentDirEntryIndex = UINT_MAX /*UINT32_MAX*/;
//      break;
    case '\n':
      stop = TRUE;
      break;
#ifdef XCURSES
    case KEY_ESC:
    {
#else
    case 27:
      c = wgetch(inputWindow);
      if( c == ERR)
      {
//    default:
//      if(ESCkeyPressed(c) )
      stop = TRUE;
      currentListBoxEntryIndex = UINT_MAX /*UINT32_MAX*/;
      }
      break;          
    }
#endif
  }
  wclear(inputWindow);
  delwin(inputWindow);
  touchwin(pBodyWindow);
  wmove(pBodyWindow, oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow);
  wrefresh(pBodyWindow);
  return currentListBoxEntryIndex;
}
