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
  ListBox::~ListBox()
  {
    FreeMemory();
  }
  
//  void ListBox::create(const char * listBoxItems [], int numberOfListBoxEntries)
//  {
////    create();
//    m_windowHandle = //Curses::Window::CreateWindowRelativePos();
//      newwin(0,0,1,1);
////    FreeMemory();
//    /** Copy array */
//    m_listBoxItems = new char *[numberOfListBoxEntries];
//    for( int index = 0; index < numberOfListBoxEntries; index++)
//    {
//      const int numChars = strlen(listBoxItems[index]) + 1;
//      char * pch = new char[numChars ];
//      if( pch )
//      {
//        memcpy(pch, listBoxItems[index], numChars);
//        m_listBoxItems[index] = pch;
//      }
//    }
//    m_numberOfListBoxEntries = numberOfListBoxEntries;
//  }
  
  void ListBox::FreeMemory()
  {
    if( m_listBoxItems)
    {
      for(int index = 0; index < m_numberOfListBoxEntries; index ++)
      {
        delete [] m_listBoxItems[index];
      }
      delete [] m_listBoxItems;
      /** Set to NULL because this function may be called multiple times. */
      m_listBoxItems = NULL;
    }
  }
  
  std::string ListBox::GetCurrentSelectionString() const
  {
    if(m_currentListBoxEntryIndex < m_numberOfListBoxEntries)
      return m_listBoxItems[m_currentListBoxEntryIndex];
    return "";
  }
  
  void ListBox::show()
  {
    wclear(m_windowHandle);
    int maxx;
#ifdef PDCURSES
    m_numberOfLinesForListBoxEntries = getmaxy(m_windowHandle);
    maxx = getmaxx(m_windowHandle);
#else
    getmaxyx(m_windowHandle, m_numberOfLinesForListBoxEntries, maxx);
#endif
//    mvwprintw(m_windowHandle, 0, 0, "%s", title);
    setcolor(m_windowHandle, m_colorPair);
    int yPos = 0;
    for(unsigned currentListEntryIndex = m_firstListBoxEntryToShow; 
      currentListEntryIndex < m_numberOfListBoxEntries &&
      yPos < m_numberOfLinesForListBoxEntries;
      currentListEntryIndex++)
    {
      if(currentListEntryIndex == m_currentListBoxEntryIndex)
        setcolor(m_windowHandle, m_currentSelectionColorPair);
      yPos = currentListEntryIndex - m_firstListBoxEntryToShow;
      /*mvwprintw*/mvwaddstr(m_windowHandle, 
        yPos, 
        1, /*"%s",*/ 
        m_listBoxItems[currentListEntryIndex]);
      if(currentListEntryIndex == m_currentListBoxEntryIndex)
        setcolor(m_windowHandle, m_colorPair);
    }
//    outputListBoxItems(m_firstListBoxEntryToShow, m_listBoxItems,
//      m_numberOfListBoxEntries, m_title, m_windowHandle);
//    touchwin(m_windowHandle);
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
      case KEY_ENTER:
      case 0xA:
        return 0xA;
        break;
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
  
  void ListBox::SetContent(std::vector<std::string> & content)
  {
    FreeMemory();
    /** Copy array */
    m_listBoxItems = new char *[content.size()];
    m_numberOfListBoxEntries = content.size();
    std::vector<std::string>::const_iterator iter = content.begin();
    for( int index = 0; index < m_numberOfListBoxEntries; index++, iter ++)
    {
      const int numChars = iter->size() + 1;
      char * pch = new char[numChars];
      if( pch )
      {
        memcpy(pch, iter->c_str(), numChars);
        m_listBoxItems[index] = pch;
      }
    }
  }
}
  