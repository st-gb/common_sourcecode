/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * Windows_log_file_prefix.hpp
 *
 *  Created on: 15.09.2011
 *      Author: Stefan
 */

#ifndef WINDOWS_LOG_FILE_PREFIX_HPP_
#define WINDOWS_LOG_FILE_PREFIX_HPP_

//there were compile errors when windows.h was included.
#include <windows.h> //for SYSTEMTIME, GetLocalTime(SYSTEMTIME)
#include "LogFileEntry.hpp" //class LogFileEntry
#include <Controller/multithread/I_Thread.hpp> //class I_Thread

#define USE_SYSTEM_TIME_FOR_LOGGING

inline void outputLogFilePrefixViaSystemTime(std::ostream & r_ostream)
{
  static FILETIME s_filetime ;
  static SYSTEMTIME s_systemtime ;
  //from en wikipedia: "System_time"
  ::GetSystemTimeAsFileTime( & s_filetime );

  ::FileTimeToSystemTime( & s_filetime, & s_systemtime);

  r_ostream
    << s_systemtime.wYear << "."
    << s_systemtime.wMonth << "."
    << s_systemtime.wDay << " "
    << s_systemtime.wHour << "h:"
    << s_systemtime.wMinute << "min "
    << s_systemtime.wSecond << "s "
    << s_systemtime.wMilliseconds << "ms"
    << " thread ID:" << ::GetCurrentThreadId()
    << ":"
    ;
}

inline void outputLogFilePrefixViaGetLocalTime(std::ostream & r_ostream)
{
  static SYSTEMTIME s_systemtime ;

  //Gets the same time as the Windows clock.
  ::GetLocalTime( & s_systemtime );

  r_ostream
    << s_systemtime.wYear << "."
    << s_systemtime.wMonth << "."
    << s_systemtime.wDay << " "
    << s_systemtime.wHour << "h:"
    << s_systemtime.wMinute << "min "
    << s_systemtime.wSecond << "s "
    << s_systemtime.wMilliseconds << "ms"
    << " thread ID:" << ::GetCurrentThreadId()
    << ":"
    ;
}

inline void outputLogFilePrefix(std::ostream & r_ostream)
{
#ifdef USE_SYSTEM_TIME_FOR_LOGGING
  outputLogFilePrefixViaSystemTime(r_ostream);
#else
  outputLogFilePrefixViaGetLocalTime(r_ostream);
#endif
}

inline void outputDateAndTimeInHTMLFormat(std::ostream & r_ostream)
{
  static SYSTEMTIME s_systemtime ;

  //Gets the same time as the Windows clock.
  ::GetLocalTime( & s_systemtime );

  r_ostream
    << s_systemtime.wMonth << "."
    << s_systemtime.wDay << "&nbsp;"
    << s_systemtime.wHour << ":" //"h:"
    << s_systemtime.wMinute << "&nbsp;"
    << s_systemtime.wSecond << "s "
    << s_systemtime.wMilliseconds << "ms"
    ;
}

inline void GetLogFilePrefixFromSystemTime(LogFileEntry & logfileentry)
{
  static SYSTEMTIME s_systemtime ;

  //Gets the same time as the Windows clock.
  ::GetLocalTime( & s_systemtime );

  logfileentry.year = s_systemtime.wYear;
  logfileentry.month = s_systemtime.wMonth;
  logfileentry.day = s_systemtime.wDay;
  logfileentry.hour = s_systemtime.wHour;
  logfileentry.minute = s_systemtime.wMinute;
  logfileentry.second = s_systemtime.wSecond;
  logfileentry.millisecond = s_systemtime.wMilliseconds;
  logfileentry.threadID = ::GetCurrentThreadId();
  I_Thread::threadNameMapType::const_iterator c_iter =
    I_Thread::s_threadNumber2Name.find(logfileentry.threadID);
  if( c_iter != I_Thread::s_threadNumber2Name.end() )
  {
    logfileentry.p_std_strThreadName = & (std::string &) c_iter->second;
  }
  else
    logfileentry.p_std_strThreadName = NULL;
}

inline void GetLogFileEntry(const FILETIME & filetime,
  LogFileEntry & logfileentry)
{
  static SYSTEMTIME s_systemtime ;
  //http://msdn.microsoft.com/en-us/library/windows/desktop/ms724277%28v=vs.85%29.aspx:
  //Convert from UTC time to local time.
  ::FileTimeToLocalFileTime(& filetime, (FILETIME *) & filetime);
  ::FileTimeToSystemTime( & filetime, & s_systemtime);

  logfileentry.year = s_systemtime.wYear;
  logfileentry.month = s_systemtime.wMonth;
  logfileentry.day = s_systemtime.wDay;
  logfileentry.hour = s_systemtime.wHour;
  logfileentry.minute = s_systemtime.wMinute;
  logfileentry.second = s_systemtime.wSecond;
  logfileentry.millisecond = s_systemtime.wMilliseconds;
//  //http://msdn.microsoft.com/en-us/library/windows/desktop/ms724284%28v=vs.85%29.aspx:
//  //"Contains a 64-bit value representing the number of 100-nanosecond
//  //intervals since January 1, 1601 (UTC)."
//  logfileentry.nanosecond = (filetime.dwLowDateTime %
//    //10 * 100;
//    //Get microseconds (10000 * 100 ns = 1000 us)
//    10000 // / 100
//    )
//    //-> nanoseconds because values are 100 ns intervalls
//    * 100;

  logfileentry.microsecond = (uint16_t) (filetime.dwLowDateTime
    & 0xFFFF
    //Get in [100 ns ... 999900 ns]
    //% 10000
    )
    //[1 us ... 999 us]
//    / 10//000
//    % 1000
    ;
}

inline void GetLogFilePrefixFromFileTime(LogFileEntry & logfileentry)
{
  static FILETIME s_filetime ;

  //from en wikipedia: "System_time"
  //"The information is in Coordinated Universal Time (UTC) format."
  ::GetSystemTimeAsFileTime( & s_filetime );

  GetLogFileEntry(s_filetime, logfileentry);
  logfileentry.threadID = ::GetCurrentThreadId();
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  logfileentry.p_std_strThreadName = I_Thread::GetThreadName(logfileentry.threadID);
#endif
}

inline void GetLogFilePrefix(LogFileEntry & logfileentry)
{
#ifdef USE_SYSTEM_TIME_FOR_LOGGING_
  GetLogFilePrefixFromSystemTime(logfileentry);
#else
  GetLogFilePrefixFromFileTime(logfileentry);
#endif
}

#endif /* WINDOWS_LOG_FILE_PREFIX_HPP_ */
