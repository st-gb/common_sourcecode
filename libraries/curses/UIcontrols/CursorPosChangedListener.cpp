/** File:   CurorPosChangedListener.cpp
 * Author: sg
 * Created on 6. Februar 2018, 17:40  */

#include "CursorPosChangedListener.hpp"
#include <stddef.h> //NULL

namespace curses
{
CursorPosChangedListener::CursorPosChangedListener()
  : m_pTextBox(NULL)
{
}

CursorPosChangedListener::~CursorPosChangedListener() {
}

void CursorPosChangedListener::Notify()
{
  
}

}
