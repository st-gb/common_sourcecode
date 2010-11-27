/*
 * AppendCurrentTimeToString.cpp
 *
 *  Created on: Nov 5, 2010
 *      Author: Stefan
 */
//Make "windows.h" as the 1st include: else g++ compilation errors like
// "error: `GetDateFormatW' cannot be used as a function"
#include <windows.h> //::GetSystemTime(...)
//For indirectly including class CString.
#include "AppendCurrentTimeToString.hpp"
//#include <string> //std::string
#include <tchar.h> //TCHAR, _T(..)

void AppendCurrentTimeToString(
  CString & cr_stdstring
//    std::string & cr_stdstring
  )
{
  //To copy indirect (that means to copy to an INTERMEDIATE filename
  //and rename afterwards) is the SAFER method. Imagine that one
  //copies to a filename that belongs to a file with a previously
  //modified version that has important changes. And then the content
  //of this file is overwritten with the new content. And when then
  //the write process doesn't finish, the destination file may be
  //unusable and the BACKUP purpose is not satisfied.
  //Probably it's also better to take a temporary filename if the final
  //file name (without time) not already exists?(because it may be
  //created while copying)
  TCHAR ar_tchDate[_MAX_PATH];
  SYSTEMTIME systemtime;
  ::GetSystemTime( & systemtime);
  //If the function fails, the return value is zero.
  if( ::GetDateFormat(
      LOCALE_USER_DEFAULT,               // locale
      DATE_SHORTDATE,             // options
      & systemtime,  // date
      NULL,          // date format
      ar_tchDate,          // formatted string buffer
      _MAX_PATH                // size of buffer
      )
    )
  {
    TCHAR ar_tchTimeString[100];
//      CHAR ar_chTimeStr[100];
    //Don't use colons (':') because pathes with colons are invalid.
    TCHAR ar_tchFormat[100] = _T("hh'.'mm'.'ss") ;
//      CHAR ar_chFormat[100] = "hh'.'mm'.'ss";
    //If the function fails, the return value is zero.
    if( ::GetTimeFormat(
        //::GetTimeFormatA(
        LOCALE_USER_DEFAULT,              // locale
        TIME_FORCE24HOURFORMAT,            // options
        & systemtime, // time
        //"If lpFormat is NULL, the function uses the time format of the
        //specified locale."
        ar_tchFormat,         // time format string
//          ar_chFormat,         // time format string
        ar_tchTimeString,         // formatted string buffer
//          ar_chTimeStr,         // formatted string buffer
        99               // size of string buffer
        )
      )
      //So we better copy to a destination file with intermediate
      //filename. Let's append the time of when the copying starts to
      //the filename. SO one knows what the file stands for if the
      //transaction of indirect copy is not finished, that means, if
      //for example THIS program crashes or the connection disconnects.
//        rstr += strDate + CString(lpTimeStr) ;
      cr_stdstring += ar_tchTimeString ;
//          ar_chTimeStr ;
  }
}
