/*
 * javautilloggingFormatter.hpp
 *
 *  Created on: 17.12.2012
 *      Author: Stefan
 */

#ifndef JAVAUTILLOGGINGFORMATTER_HPP_
#define JAVAUTILLOGGINGFORMATTER_HPP_

#include "ILogFormatter.hpp"
//GetClassName(...), GetFunctionName(...)
#include <compiler/current_function.hpp>

namespace CSS
{
  namespace LogFormatter
  {
    /** Class that aims to write Log4J compliant log files.*/
    class Log4jFormatter
      : public I_LogFormatter
    {
    public:
      Log4jFormatter(const Logger * p_logger);
      virtual
      ~Log4jFormatter();

      /** @see http://logging.apache.org/log4j/1.2/apidocs/org/apache/log4j/Level.html
       * All strings must contain <= 5 characters for log file viewers? */
      //inline
        char * GetLogLevelAsString(enum MessageType messageType);

      /** Write log file in "%d{ISO8601} [%t] C M %m%n" format/ pattern
       * -"%d{ISO8601}" : current time in ISO8601 format
       * -"%t" : thread name
       * -"C" : class name
       * -"M" : method name
       * -"%m" : message
       * -"%n" : new line in OS-specific (Mac: "\r", Linux: "\n" Windows: "\r\n"
       *   encoding
       * */
      virtual void WriteLogFileEntry(
        const LogFileEntry & logfileentry,
        enum MessageType messageType = LogLevel::info,
        const char * const prettyFunctionFormattedFunctionName = NULL
        )
      {
    //    static std::string std_strTime;
        GetTimeAsString(logfileentry//, std_strTime
          );
        if( prettyFunctionFormattedFunctionName)
          * m_p_std_ostream
            << m_p_chTimeString << " "
            << GetLogLevelAsString(messageType) << " "
            << "[" "Thread-"
            << logfileentry.threadID << "] "
            //  e.g. "[Thread-1]"
            << GetClassName(//__PRETTY_FUNCTION__
              prettyFunctionFormattedFunctionName) << " "
            << GetFunctionName(//__PRETTY_FUNCTION__
              prettyFunctionFormattedFunctionName) << " "
            << * logfileentry.p_std_strMessage //<< std::endl
  //          << " thread ID:" << logfileentry.threadID << " "
      //      << "\n"
            ;
      }
    };
  } /* namespace LogFormatter */
} /* namespace CSS */
#endif /* JAVAUTILLOGGINGFORMATTER_HPP_ */
