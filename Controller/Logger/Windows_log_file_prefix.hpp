/*
 * Windows_log_file_prefix.hpp
 *
 *  Created on: 15.09.2011
 *      Author: Stefan
 */

#ifndef WINDOWS_LOG_FILE_PREFIX_HPP_
#define WINDOWS_LOG_FILE_PREFIX_HPP_

inline void outputLogFilePrefix(std::ostream & r_ostream)
{
  static SYSTEMTIME m_systemtime ;

  //Gets the same time as the Windows clock.
  ::GetLocalTime( & m_systemtime );

  r_ostream
    << m_systemtime.wYear << "."
    << m_systemtime.wMonth << "."
    << m_systemtime.wDay << " "
    << m_systemtime.wHour << "h:"
    << m_systemtime.wMinute << "min "
    << m_systemtime.wSecond << "s "
    << m_systemtime.wMilliseconds << "ms"
    << " thread ID:" << ::GetCurrentThreadId()
    << ":"
    ;
}

#endif /* WINDOWS_LOG_FILE_PREFIX_HPP_ */
