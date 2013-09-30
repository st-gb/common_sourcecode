/*
 * ConsoleOutputHandler.hpp
 *
 *  Created on: 17.02.2013
 *      Author: Stefan
 */

#ifndef CONSOLEFORMATTER_HPP_
#define CONSOLEFORMATTER_HPP_

//#include <Controller/Logger/OutputHandler/I_LogEntryOutputter.hpp>
#include <Controller/Logger/Formatter/I_LogFormatter.hpp>
#include <windows.h> //HANDLE

//Forward decl.
class FormattedLogEntryProcessor;

//from http://lovelyscripts.webs.com/c.htm
#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN

namespace Windows
{
  class ConsoleFormatter
    : //public I_LogEntryOutputter
      public I_LogFormatter
  {
    HANDLE m_hStdout;
    WORD m_wOldColorAttrs;
  public:
    ConsoleFormatter(const FormattedLogEntryProcessor *
      p_formattedlogentryprocessor)
      : I_LogFormatter(p_formattedlogentryprocessor)
    {
      //http://msdn.microsoft.com/en-us/library/windows/desktop/ms686974%28v=vs.85%29.aspx
      CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
      m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
      if ( m_hStdout != INVALID_HANDLE_VALUE &&
          GetConsoleScreenBufferInfo(m_hStdout, & csbiInfo) )
      {
        m_wOldColorAttrs = csbiInfo.wAttributes;
  //      m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
      }
      else
        m_wOldColorAttrs = FOREGROUND_INTENSITY;
  //      throw std::exception();
    }
    virtual
    ~ConsoleFormatter();
    void SetColor(enum MessageType messageType)
    {
      switch( messageType)
      {
        case LogLevel::error:
          //from http://stackoverflow.com/questions/9262270/color-console-output-with-c-in-windows
          SetConsoleTextAttribute(m_hStdout, FOREGROUND_RED |
            FOREGROUND_INTENSITY);
          break;
        case LogLevel::success:
          //from http://stackoverflow.com/questions/9262270/color-console-output-with-c-in-windows
          SetConsoleTextAttribute(m_hStdout, FOREGROUND_GREEN |
            FOREGROUND_INTENSITY);
          break;
        case LogLevel::warning:
          //from http://stackoverflow.com/questions/9262270/color-console-output-with-c-in-windows
          SetConsoleTextAttribute(m_hStdout, FOREGROUND_YELLOW |
            FOREGROUND_INTENSITY);
          break;
        default:
          SetConsoleTextAttribute(m_hStdout, m_wOldColorAttrs);
          break;
      }
    }
    void WriteLogFileEntry(
      const LogFileEntry & logfileentry,
      enum MessageType messageType = LogLevel::info,
      const char * const prettyFunctionFormattedFunctionName = NULL
      );

    void WriteMessage(const std::string & r_std_strMessage,
      enum MessageType messageType = LogLevel::info)
    {
  //    static std::string std_strTime;
//      GetTimeAsString(logfileentry//, std_strTime
//        );
      * m_p_std_ostream
//        << m_p_chTimeString
//        << " thread ID:" << logfileentry.threadID << " "
        << r_std_strMessage
  //      << "\n"
        ;
    }
  };
} /* namespace Windows */

#endif /* CONSOLEFORMATTER_HPP_ */
