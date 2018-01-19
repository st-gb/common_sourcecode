#include <curses.h> //WINDOW
#include <limits.h> //UINT_MAX
#include <string.h> //strlen(...)

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
  int numberOfLinesForInputBox, numberOfColumnsForInputBox, currentDirEntryIndex,
    currentDescStringLength,
    maxFieldDescInChars = 0;
  int numberOfDirectoryEntries;
  int c = 0;
  bool stop = FALSE;

  for (numberOfDirectoryEntries = 0; /** last element has to be NULL */
    listBoxItems[numberOfDirectoryEntries] &&
    (currentDescStringLength = strlen(listBoxItems[numberOfDirectoryEntries]) ) > 0;
    numberOfDirectoryEntries++)
  {
    if( currentDescStringLength > maxFieldDescInChars)
      maxFieldDescInChars = currentDescStringLength;
  }

  const unsigned titleLenghtInChars = strlen(title);

  /** numberOfInputWindows ^= number of fields now */
  numberOfLinesForInputBox = numberOfDirectoryEntries + 2;
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

  outputDirEntriesList(0, listBoxItems, numberOfDirectoryEntries, 
    title, inputWindow);

  const int selectionMarkerYpos = 1;
  mvwprintw(inputWindow, 1, selectionMarkerYpos, "%c", 'x');
  
  const unsigned numberOfLinesForDirEntries = numberOfLinesForInputBox - 1;

  currentDirEntryIndex = 0;
//    unsigned selectionIndex;
  unsigned firstDirEntryToShow = 0;
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
      if( currentDirEntryIndex > 0)
      {
        currentDirEntryIndex --;
      if( currentDirEntryIndex < firstDirEntryToShow )
      {
        outputDirEntriesList(--firstDirEntryToShow, listBoxItems,
          numberOfDirectoryEntries, title, inputWindow);
        mvwprintw(inputWindow, 1, selectionMarkerYpos, "%c", 'x');
      }
      else
        if( numberOfDirectoryEntries > 0) /** Prevent division by 0. */
        {
          const int lineNumber = currentDirEntryIndex - firstDirEntryToShow + 1;
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
      if( currentDirEntryIndex + 1 < numberOfDirectoryEntries)
      {
          currentDirEntryIndex++;
      if( currentDirEntryIndex - firstDirEntryToShow + 1 > numberOfLinesForDirEntries )
      {
//        firstDirEntryToShow = currentDirEntryIndex - 
//          numberOfLinesForDirEntries + 1;
        firstDirEntryToShow++;
        outputDirEntriesList(firstDirEntryToShow, listBoxItems, 
          numberOfDirectoryEntries, title, inputWindow);
//        wrefresh(pBodyWindow);
        mvwprintw(inputWindow, numberOfLinesForDirEntries, selectionMarkerYpos, "%c", 'x');
      }
      else
      {
          const int lineNumber = currentDirEntryIndex - firstDirEntryToShow;
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
      currentDirEntryIndex = UINT_MAX /*UINT32_MAX*/;
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
  return currentDirEntryIndex;
}
