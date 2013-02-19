/*
 * JavaUtilLoggingFormatter.cpp
 *
 *  Created on: 17.12.2012
 *      Author: Stefan
 */

#include "Log4jFormatter.hpp"

namespace CSS
{
  namespace LogFormatter
  {

    Log4jFormatter::Log4jFormatter(const /*Logger * p_logger*/
//      I_LogEntryOutputter * p_outputhandler
      FormattedLogEntryProcessor * appender
      )
      : I_LogFormatter(/*p_logger p_outputhandler*/ appender)
    {
      //Calling this method is needed(!?) if "m_p_chTimeString" was created before.
      SetTimeFormat(
        //        "%day%.%month%.%year% %hour%:%minute%:%second%,%millisecond%";
        //see http://logging.apache.org/log4j/1.2/apidocs/org/apache/log4j/helpers/ISO8601DateFormat.html:
        // "yyyy-MM-dd HH:mm:ss,SSS" for example "1999-11-27 15:49:37,459".
        "%year%-%month%-%day% %hour%:%minute%:%second%,%millisecond%");
    }

    Log4jFormatter::~Log4jFormatter()
    {
      // TODO Auto-generated destructor stub
    }

    inline char * Log4jFormatter::GetLogLevelAsString(
      enum MessageType messageType)
    {
      switch(messageType)
      {
        case LogLevel::debug:
          //By "(char *)": avoid g++ warning "deprecated conversion from
          //string constant to ‘char*’"
          return (char *) "DEBUG";
        case LogLevel::info:
          //By "(char *)": avoid g++ warning "deprecated conversion from
          //string constant to ‘char*’"
          return (char *) "INFO";
        case LogLevel::warning:
          //Must NOT be "WARNING" else it was shown as level "FINE" in Otros
          //log file viewer
          //By "(char *)": avoid g++ warning "deprecated conversion from
          //string constant to ‘char*’"
          return (char *) "WARN";
        case LogLevel::error:
          //By "(char *)": avoid g++ warning "deprecated conversion from
          //string constant to ‘char*’"
          return (char *) "ERROR";
        //Unused, but if not handled: g++ warning
        case LogLevel::beyondLastLogMessageType:
        case LogLevel::success:
          break;
      }
      //By "(char *)": avoid g++ warning "deprecated conversion from
      //string constant to ‘char*’"
      return (char *) "UNKNOWN";
    }
  } /* namespace LogFormatter */
} /* namespace CSS */
