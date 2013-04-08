/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
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
