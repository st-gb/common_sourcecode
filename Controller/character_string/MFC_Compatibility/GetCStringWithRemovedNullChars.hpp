/*
 * GetCStringWithRemovedNullChars.hpp
 *
 *  Created on: Nov 26, 2010
 *      Author: Stefan
 */

#ifndef GETCSTRINGWITHREMOVEDNULLCHARS_HPP_
#define GETCSTRINGWITHREMOVEDNULLCHARS_HPP_

#ifndef _MFC_VER
  //class MFC_Compatibility::CString
  #include <Controller/character_string/MFC_Compatibility/CString.hpp>
  using namespace MFC_Compatibility ;
#endif

typedef unsigned short WORD ;

//weil CString( LPCTSTR lpch, int nLength ); nicht richtig funzte
//geht anscheinend nur biszum ersten 0-Zeichen
CString GetCStringWithRemovedNullChars(
  char * pchFirstChar,
  WORD wNumberOfCharsToCopy) ;

#endif /* GETCSTRINGWITHREMOVEDNULLCHARS_HPP_ */
