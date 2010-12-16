/*
 * URL.cpp
 *
 *  Created on: Nov 13, 2010
 *      Author: Stefan
 */
#include "URL.hpp" //class CString
#include <tchar.h> //_T(...)

//Um das Passwort eines Zielverzeichnis, das auf einem FTP-Server liegt,
//zu verstecken. Often it is unwanted for the user that this password is
//shown on the display.
CString PossiblyHidePassword(
  const CString & cr_strOrginalDestinationPath//,
  //CString & rstrModifiedDestinationPath
  )
{
  CString strModifiedDestinationPath;
  int nIndexRightOfSecondColon, nIndexOfFirstATcharacterAfterFirstColon;
  //ein FTP-String sieht bespielsweise so aus:
  //ftp://ftp_stefan%40c-heffner.de:swordfish@ftp.strato.com
  nIndexRightOfSecondColon = cr_strOrginalDestinationPath.Find(':');
  //wenn (mindestens) ein Doppelpunkt in der Zeichenkette vorkommt
  if( nIndexRightOfSecondColon > 0 && cr_strOrginalDestinationPath.
    GetLength() > ++ nIndexRightOfSecondColon )
  {
    nIndexRightOfSecondColon = cr_strOrginalDestinationPath.Find(':',
      //The index of the character in the string to begin the
      //search with, or 0 to start from the beginning.
      nIndexRightOfSecondColon);
    //-1 if the substring or character is not found.
    //wenn (mindestens) 2 Doppelpunkte in der Zeichenkette vorkommen
    if( nIndexRightOfSecondColon > 0 )
    {
      nIndexOfFirstATcharacterAfterFirstColon =
        cr_strOrginalDestinationPath.Find('@',nIndexRightOfSecondColon);
      //und nach diesem Doppelpunkt noch ein @-Zeichen vorkommt
      //und zwischen den beiden Zeichen mind. 1 weiteres Zeichen liegt
      if(nIndexOfFirstATcharacterAfterFirstColon > nIndexRightOfSecondColon)
      {
        strModifiedDestinationPath = cr_strOrginalDestinationPath;
        strModifiedDestinationPath.Delete(
          //The zero-based index of the first character in the
          //CStringT object to delete
          ++ nIndexRightOfSecondColon,
          //# of chars to delete
          nIndexOfFirstATcharacterAfterFirstColon - nIndexRightOfSecondColon);
        strModifiedDestinationPath.Insert(
          //The index of the character before which the insertion will take place.
          nIndexRightOfSecondColon,
          _T("PASS") );
      }
    }
  }
  return strModifiedDestinationPath;
}
