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

//namespace Logger
//{
  class ConsoleFormatter
    : //public I_LogEntryOutputter
      public I_LogFormatter
  {
    HANDLE m_hStdout;
    WORD m_wOldColorAttrs;
  public:
    ConsoleFormatter(const FormattedLogEntryProcessor * );
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
        case LogLevel::warning:
          //from http://stackoverflow.com/questions/9262270/color-console-output-with-c-in-windows
          SetConsoleTextAttribute(m_hStdout, FOREGROUND_BLUE |
            FOREGROUND_INTENSITY);
          break;
        default:
          SetConsoleTextAttribute(m_hStdout, m_wOldColorAttrs);
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

//} /* namespace Logger */
#endif /* CONSOLEFORMATTER_HPP_ */
