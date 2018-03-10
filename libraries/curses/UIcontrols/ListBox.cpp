#include "ListBox.hpp"
#include "../listbox.h"
#include <string.h> //memcpy(...)
#include "../color.h"
#include "drawScrollBar.h"

namespace curses
{
//  ListBox::ListBox()
//  {
//  }
  
  void ListBox::create(const char * listBoxItems [], int numberOfListBoxEntries)
  {
//    create();
    m_windowHandle = //Curses::Window::CreateWindowRelativePos();
      newwin(0,0,1,1);
    /** Copy array */
    m_listBoxItems = new char *[numberOfListBoxEntries];
    for( int index = 0; index < numberOfListBoxEntries; index++)
    {
      const int numChars = strlen(listBoxItems[index]) + 1;
      char * pch = new char[numChars ];
      if( pch )
      {
        memcpy(pch, listBoxItems[index], numChars);
        m_listBoxItems[index] = pch;
      }
    }
    m_numberOfListBoxEntries = numberOfListBoxEntries;
  }
  
  ListBox::~ListBox()
  {
    if( m_listBoxItems)
    {
      for(int index = 0; index < m_numberOfListBoxEntries; index ++)
      {
        delete [] m_listBoxItems[index];
      }
      delete [] m_listBoxItems;
//      m_listBoxItems = NULL;
    }
  }
  
  void ListBox::show()
  {
    wclear(m_windowHandle);
//    mvwprintw(m_windowHandle, 0, 0, "%s", title);
    int yPos;
    for(unsigned currentListEntryIndex = m_firstListBoxEntryToShow; 
      currentListEntryIndex < m_numberOfListBoxEntries;
      currentListEntryIndex++)
    {
      if(currentListEntryIndex == m_currentListBoxEntryIndex)
        setcolor(m_windowHandle, m_currentSelectionColorPair);
      yPos = currentListEntryIndex - m_firstListBoxEntryToShow + 1;
      mvwprintw(m_windowHandle, 
        yPos, 
        1, "%s", m_listBoxItems[currentListEntryIndex]);
      if(currentListEntryIndex == m_currentListBoxEntryIndex)
        setcolor(m_windowHandle, m_backGroundColorPair);
    }
//    outputListBoxItems(m_firstListBoxEntryToShow, m_listBoxItems,
//      m_numberOfListBoxEntries, m_title, m_windowHandle);
//    touchwin(m_windowHandle);
    int maxx;
#ifdef PDCURSES
    m_numberOfLinesForListBoxEntries = getmaxy(m_windowHandle);
    maxx = getmaxx(m_windowHandle);
#else
    getmaxyx(m_windowHandle, m_numberOfLinesForListBoxEntries, maxx);
#endif
    drawScrollBar(
      m_windowHandle, 
      m_numberOfListBoxEntries, 
      m_numberOfLinesForListBoxEntries,
      m_firstListBoxEntryToShow, 
      0
      );
    wrefresh(m_windowHandle);
  }
  
void ListBox::HandleKeyDown()
{
//      if( currentDirEntryIndex == numberOfDirectoryEntries - 1)
//        currentDirEntryIndex = 0;
//      else
//        ++currentDirEntryIndex;
  if( m_currentListBoxEntryIndex + 1 < m_numberOfListBoxEntries)
  {
      m_currentListBoxEntryIndex++;
  if( m_currentListBoxEntryIndex - m_firstListBoxEntryToShow + 1 > m_numberOfLinesForListBoxEntries )
  {
//        firstDirEntryToShow = currentDirEntryIndex - 
//          numberOfLinesForDirEntries + 1;
    m_firstListBoxEntryToShow++;
    drawScrollBar(
      m_windowHandle, 
      m_numberOfListBoxEntries, 
      m_numberOfLinesForListBoxEntries,
      m_firstListBoxEntryToShow, 
      0
      );
  }
  else
  {
    const int lineNumber = m_currentListBoxEntryIndex - m_firstListBoxEntryToShow;
  }
    show();
  }
}
  
void ListBox::HandleKeyUp()
{
//      currentDirEntryIndex = (currentDirEntryIndex + numberOfDirectoryEntries 
//        - 1) % numberOfDirectoryEntries;
  if( m_currentListBoxEntryIndex > 0)
  {
    m_currentListBoxEntryIndex --;
  if( m_currentListBoxEntryIndex < m_firstListBoxEntryToShow )
  {
    -- m_firstListBoxEntryToShow;
    //https://stackoverflow.com/questions/6617419/add-a-scrollbar-on-ncurses-or-make-it-like-more
//        mvwprintw(, 1, 0, "%c", 0x25B2);
//    drawScrollBar();
  }
  else
    if( m_numberOfListBoxEntries > 0) /** Prevent division by 0. */
    {
      const int lineNumber = m_currentListBoxEntryIndex - m_firstListBoxEntryToShow + 1;
    }
    show();
  }
}

  int ListBox::HandleAction(const int ch)
  {
    switch (ch)
    {
    case ERR: /** Nothing typed. */
      break;
    case KEY_UP:
      HandleKeyUp();
      break;
    case '\t':
    case KEY_DOWN:
      HandleKeyDown();
      break;
//    case '\n':
//      break;
      default:
        return -1;
    }
    return 0;
  }
}