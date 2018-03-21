#include <curses.h> //WINDOW
#include <limits.h> //UINT_MAX
#include <string.h> //strlen(...)
#include "UIcontrols/drawScrollBar.h"

#ifndef mvwinputbox
  #define mvwinputbox(w,y,x,l,c) (wmove(w,y,x)==ERR?w:winputbox(w,l,c))
#endif

void outputListBoxItems(
  unsigned firstIndex, 
  const char * const listBoxItems [], 
  const unsigned numberOfListBoxEntries,
//  const unsigned numberOfLinesForInputBox,
  const char title [],  
  WINDOW * inputWindow
  )
{
  wclear(inputWindow);
  mvwprintw(inputWindow, 0, 0, "%s", title);
  for(unsigned currentDirEntryIndex = firstIndex; 
    currentDirEntryIndex < numberOfListBoxEntries;
    currentDirEntryIndex++)
    mvwprintw(inputWindow, 
      currentDirEntryIndex - firstIndex + 1, 
      3, "%s", listBoxItems[currentDirEntryIndex]);
//  touchwin(inputWindow);
//  wrefresh(inputWindow);
}

void showCurrentSelection(
  WINDOW * inputWindow,
  int xPos,
  int yPos,
  chtype backGroundColorPair, 
  chtype currentSelectionColorPair,
  char selectedString []
  )
{
  //mvwprintw(inputWindow, 1, yPos, "%c", 'x');
  color_set(currentSelectionColorPair, 0);
  mvwprintw(inputWindow, yPos, xPos, "%s", selectedString);
  color_set(backGroundColorPair, 0);
}

void GetNumListBoxEntriesAndMaxLength(
  const char * const listBoxItems[],
//  int * p_numberOfListBoxEntries,
  int numberOfListBoxEntries,
  int * p_maxFieldDescInChars
  )
{
  int currentListBoxItemStringLength;
  for (//*p_numberOfListBoxEntries = 0; /** last element has to be NULL */
    //listBoxItems[*p_numberOfListBoxEntries] &&
    //(currentListBoxItemStringLength = strlen(listBoxItems[*p_numberOfListBoxEntries]) ) > 0;
    //*p_numberOfListBoxEntries++
    ; numberOfListBoxEntries > 0 ; numberOfListBoxEntries --
    )
  {
    if( currentListBoxItemStringLength > *p_maxFieldDescInChars)
      *p_maxFieldDescInChars = currentListBoxItemStringLength;
  }
}

void HandleKeyDown(
  WINDOW * inputWindow,
  const char * const listBoxItems[],
  const char title[],
  int * p_currentListBoxEntryIndex,
  const int numberOfListBoxEntries,
  int * p_firstListBoxEntryToShow,
  const int numberOfLinesForListBoxEntries,
  int selectionMarkerYpos
  )
{
//      if( currentDirEntryIndex == numberOfDirectoryEntries - 1)
//        currentDirEntryIndex = 0;
//      else
//        ++currentDirEntryIndex;
  if( *p_currentListBoxEntryIndex + 1 < numberOfListBoxEntries)
  {
      *p_currentListBoxEntryIndex++;
  if( *p_currentListBoxEntryIndex - *p_firstListBoxEntryToShow + 1 > numberOfLinesForListBoxEntries )
  {
//        firstDirEntryToShow = currentDirEntryIndex - 
//          numberOfLinesForDirEntries + 1;
    *p_firstListBoxEntryToShow++;
    outputListBoxItems(*p_firstListBoxEntryToShow, listBoxItems, 
      numberOfListBoxEntries, title, inputWindow);
//        wrefresh(pBodyWindow);
    mvwprintw(inputWindow, numberOfLinesForListBoxEntries, selectionMarkerYpos, "%c", 'x');
    drawScrollBar(inputWindow, numberOfListBoxEntries, 
      numberOfLinesForListBoxEntries, *p_firstListBoxEntryToShow, 1);
  }
  else
  {
    const int lineNumber = *p_currentListBoxEntryIndex - *p_firstListBoxEntryToShow;
    /** Erase previous selection */
    mvwprintw(inputWindow, lineNumber, selectionMarkerYpos, "%c", ' ');
    /** Show current selection */
    mvwprintw(inputWindow, lineNumber + 1, selectionMarkerYpos, "%c", 'x');
  }
  }
//      stop = TRUE;
//      currentDirEntryIndex = UINT_MAX /*UINT32_MAX*/;
//      break;
}

void HandleKeyUp(
  WINDOW * inputWindow,
  const char * const listBoxItems[],
  const char title[],
  int * p_currentListBoxEntryIndex,
  const int numberOfListBoxEntries,
  int * p_firstListBoxEntryToShow,
  const int numberOfLinesForListBoxEntries,
  int selectionMarkerYpos
  )
{
//      currentDirEntryIndex = (currentDirEntryIndex + numberOfDirectoryEntries 
//        - 1) % numberOfDirectoryEntries;
  if( *p_currentListBoxEntryIndex > 0)
  {
    *p_currentListBoxEntryIndex --;
  if( *p_currentListBoxEntryIndex < *p_firstListBoxEntryToShow )
  {
    outputListBoxItems(--*p_firstListBoxEntryToShow, listBoxItems,
      numberOfListBoxEntries, title, inputWindow);
//        showCurrentSelection(inputWindow, 1, selectionMarkerYpos, 
//          backGroundColorPair, currentSelectionColorPair, 
//          listBoxItems[firstListBoxEntryToShow+selectionMarkerYpos] );
    mvwprintw(inputWindow, 1, selectionMarkerYpos, "%c", 'x');
    //https://stackoverflow.com/questions/6617419/add-a-scrollbar-on-ncurses-or-make-it-like-more
//        mvwprintw(, 1, 0, "%c", 0x25B2);
    drawScrollBar(inputWindow, numberOfListBoxEntries, 
      numberOfLinesForListBoxEntries, *p_firstListBoxEntryToShow, 1);
  }
  else
    if( numberOfListBoxEntries > 0) /** Prevent division by 0. */
    {
      const int lineNumber = *p_currentListBoxEntryIndex - *p_firstListBoxEntryToShow + 1;
      /** Erase previous selection */
      mvwprintw(inputWindow, lineNumber + 1, selectionMarkerYpos, "%c", ' ');
      mvwprintw(inputWindow, lineNumber, selectionMarkerYpos, "%c", 'x');
    }
  }
}

//TODO
/** @param listBoxItems: last element must be NULL
 *  @return selected index or UINT_MAX if ESC was pressed */
unsigned int listBox(
  const char * const listBoxItems[]/*, int field*/, 
  int numberOfListBoxEntries,
  const char title [], 
  WINDOW * pWindowToShowListBoxIn,
  chtype backGroundColorPair, 
  chtype currentSelectionColorPair
  )
{
  WINDOW * inputWindow;
  int oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow;
  int bodyWindowMaxY, bodyWindowMaxX;
  int numberOfLinesForInputBox, numberOfColumnsForInputBox, 
    currentListBoxEntryIndex, maxFieldDescInChars = 0;
//  int numberOfListBoxEntries;
  int c = 0;
  bool stop = FALSE;

  GetNumListBoxEntriesAndMaxLength(
    listBoxItems,
//    & numberOfListBoxEntries, 
    numberOfListBoxEntries,
    & maxFieldDescInChars);
  const unsigned titleLenghtInChars = strlen(title);

  /** numberOfInputWindows ^= number of fields now */
  numberOfLinesForInputBox = numberOfListBoxEntries + 2;
  numberOfColumnsForInputBox = titleLenghtInChars > maxFieldDescInChars + 4 ?
      titleLenghtInChars : maxFieldDescInChars /*+ field*/ + 4;

  /** Get current cursor x&y position of the body window "curses" function */
  getyx(pWindowToShowListBoxIn, oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow);
  getmaxyx(pWindowToShowListBoxIn, bodyWindowMaxY, bodyWindowMaxX); /* "curses" function */

  if( numberOfLinesForInputBox > bodyWindowMaxY - 1)
      numberOfLinesForInputBox = bodyWindowMaxY - 1;
  if( numberOfColumnsForInputBox > bodyWindowMaxX - 1)
      numberOfColumnsForInputBox = bodyWindowMaxX - 1;
//#ifdef PDCURSES
//  /** Place input window in center of body window. */
//  const unsigned verticalCenter = (bodyWindowMaxY - numberOfLinesForInputBox) / 2;
//  const unsigned horizontalCenter = (bodyWindowMaxX - numberOfColumnsForInputBox) / 2;
//  inputWindow = mvwinputbox(
//    pWindowToShowListBoxIn,
//    verticalCenter, horizontalCenter,
//    numberOfLinesForInputBox, numberOfColumnsForInputBox);
//#elif defined(CURSES)
//  int res = wmove(pWindowToShowListBoxIn, verticalCenter, horizontalCenter);
//  if( res != ERR)
    inputWindow = /*subwin*/derwin(
      pWindowToShowListBoxIn,
      numberOfLinesForInputBox, numberOfColumnsForInputBox,
      0, 0);
//#endif

  if( ! inputWindow)
    return 0;
    
  /** http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/init.html
   *  "enables the reading of function keys like F1, F2, arrow keys etc." */
  keypad( inputWindow, TRUE);

  mvwprintw(inputWindow, 0, 0, "%s", title);

  outputListBoxItems(0, listBoxItems, numberOfListBoxEntries, 
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
      HandleKeyUp(inputWindow, listBoxItems, title, 
        & currentListBoxEntryIndex, numberOfListBoxEntries, 
        & firstListBoxEntryToShow, numberOfLinesForListBoxEntries, 
        selectionMarkerYpos);
      break;
    case '\t':
    case KEY_DOWN:
      HandleKeyDown(inputWindow, listBoxItems, title, 
        & currentListBoxEntryIndex, numberOfListBoxEntries, 
        & firstListBoxEntryToShow, numberOfLinesForListBoxEntries, 
        selectionMarkerYpos);
      break;
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
  touchwin(pWindowToShowListBoxIn);
  wmove(pWindowToShowListBoxIn, oldYCursorPosOfBodyWindow, oldXcursorPosOfBodyWindow);
  wrefresh(pWindowToShowListBoxIn);
  return currentListBoxEntryIndex;
}
