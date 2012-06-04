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
}

inline void GetLogFilePrefixFromFileTime(LogFileEntry & logfileentry)
{
  static FILETIME s_filetime ;
  static SYSTEMTIME s_systemtime ;

  //from en wikipedia: "System_time"
  ::GetSystemTimeAsFileTime( & s_filetime );

  ::FileTimeToSystemTime( & s_filetime, & s_systemtime);

  logfileentry.year = s_systemtime.wYear;
  logfileentry.month = s_systemtime.wMonth;
  logfileentry.day = s_systemtime.wDay;
  logfileentry.hour = s_systemtime.wHour;
  logfileentry.minute = s_systemtime.wMinute;
  logfileentry.second = s_systemtime.wSecond;
  logfileentry.millisecond = s_systemtime.wMilliseconds;
  //http://msdn.microsoft.com/en-us/library/windows/desktop/ms724284%28v=vs.85%29.aspx:
  //"Contains a 64-bit value representing the number of 100-nanosecond
  //intervals since January 1, 1601 (UTC)."
  logfileentry.nanosecond = s_filetime.dwLowDateTime % 10 * 100;
  logfileentry.threadID = ::GetCurrentThreadId();
}

inline void GetLogFilePrefix(LogFileEntry & logfileentry)
{
#ifdef USE_SYSTEM_TIME_FOR_LOGGING
  GetLogFilePrefixFromSystemTime(logfileentry);
#else
  GetLogFilePrefixFromFileTime(logfileentry);
#endif
}

#endif /* WINDOWS_LOG_FILE_PREFIX_HPP_ */
