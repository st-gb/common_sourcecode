#include "ListBox.hpp"
#include "../listbox.h"
#include <string.h> //memcpy(...)

namespace curses
{
  ListBox::ListBox()
    : m_listBoxItems(NULL)
  {
  }
  
  void ListBox::create(char * listBoxItems [], int numberOfListBoxEntries)
  {
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
  
  int ListBox::HandleAction(const int ch)
  {
    switch (ch)
    {
    case ERR: /** Nothing typed. */
      break;
    case KEY_UP:
      HandleKeyUp(m_windowHandle, m_listBoxItems, m_title, 
        & m_currentListBoxEntryIndex, m_numberOfListBoxEntries, 
        & m_firstListBoxEntryToShow, m_numberOfLinesForListBoxEntries, 
        m_selectionMarkerYpos);
      break;
    case '\t':
    case KEY_DOWN:
      HandleKeyDown(m_windowHandle, m_listBoxItems, m_title, 
        & m_currentListBoxEntryIndex, m_numberOfListBoxEntries, 
        & m_firstListBoxEntryToShow, m_numberOfLinesForListBoxEntries, 
        m_selectionMarkerYpos);
      break;
//    case '\n':
//      break;
    }
  }
}