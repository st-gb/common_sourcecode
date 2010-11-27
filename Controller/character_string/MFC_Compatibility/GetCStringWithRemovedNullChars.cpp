/*
 * GetCStringWithRemovedNullChars.cpp
 *
 *  Created on: Nov 26, 2010
 *      Author: Stefan
 */
#include "GetCStringWithRemovedNullChars.hpp"

//weil CString( LPCTSTR lpch, int nLength ); nicht richtig funzte
//geht anscheinend nur biszum ersten 0-Zeichen
CString GetCStringWithRemovedNullChars(
  char * pchFirstChar,
  WORD wNumberOfCharsToCopy)
{
  CString strBack;
  for( WORD wRun = 0; wRun < wNumberOfCharsToCopy; ++ wRun, pchFirstChar ++ )
  {
    if( * pchFirstChar)//!=0
      strBack += * pchFirstChar;//++;
  }
  return strBack;
}
