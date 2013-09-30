/*
 * ConsoleOutputHandler.cpp
 *
 *  Created on: 17.02.2013
 *      Author: Stefan
 */

#include "ConsoleFormatter.hpp"
#include <windows.h>

//namespace Logger
//{
//  ConsoleFormatter::ConsoleFormatter(
//    const FormattedLogEntryProcessor * p_formattedlogentryprocessor)
//    : I_LogFormatter(p_formattedlogentryprocessor)
//  {
//    //http://msdn.microsoft.com/en-us/library/windows/desktop/ms686974%28v=vs.85%29.aspx
//    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
//    m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
//    if ( m_hStdout != INVALID_HANDLE_VALUE &&
//        GetConsoleScreenBufferInfo(m_hStdout, & csbiInfo) )
//    {
//      m_wOldColorAttrs = csbiInfo.wAttributes;
////      m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
//    }
//    else
//      m_wOldColorAttrs = FOREGROUND_INTENSITY;
////      throw std::exception();
//  }

  ConsoleFormatter::~ConsoleFormatter()
  {
    if( m_hStdout != INVALID_HANDLE_VALUE )
    {
      SetConsoleTextAttribute(m_hStdout, m_wOldColorAttrs);
    }
  }

  void ConsoleFormatter::WriteLogFileEntry(
    const LogFileEntry & logfileentry,
    enum MessageType messageType /*= LogLevel::info*/,
    const char * const prettyFunctionFormattedFunctionName //= NULL
    )
  {
    GetTimeAsString(logfileentry//, std_strTime
      );
    * m_p_std_ostream
      << m_p_chTimeString
      << " thread ID:" << logfileentry.threadID << " ";
    SetColor(messageType);
    * m_p_std_ostream
      << * logfileentry.p_std_strMessage
//      << "\n"
      ;
    SetConsoleTextAttribute(m_hStdout,//m_wOldColorAttrs
      FOREGROUND_INTENSITY);
  }
//  unsigned ConsoleOutputHandler::DoOutput()
//  {
//    std::string c_r_std_strMessage;
//    //from http://stackoverflow.com/questions/9262270/color-console-output-with-c-in-windows
//    SetConsoleTextAttribute(m_hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
////    getUTF8string_inline(c_r_std_wstrMessage, c_r_std_strMessage);
////    _cprintf("%s", c_r_std_strMessage.c_str() );
//  }
//} /* namespace Logger */
