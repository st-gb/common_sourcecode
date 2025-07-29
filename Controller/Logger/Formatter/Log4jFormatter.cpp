/**(c)from 2012:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
*Created 17.12.2012 by Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 #include "Log4jFormatter.hpp"
 //#include <compiler/castToChar.h>
 #include <compiler/GCC/avoid_write_strings_warning.h>///TU_Bln361095castToCharPtr

namespace TU_Bln361095{namespace Logger{
//TODO TU_Bln361095LoggerNmSpcBgn

Log4jFormatter::Log4jFormatter(const /*Logger * p_logger*/
//      I_LogEntryOutputter * p_outputhandler
  FormattedLogEntryProcessor * appender
  )
  : I_LogFormatter(/*p_logger p_outputhandler*/ appender)
{
  //Calling this method is needed(!?) if "m_p_chTimeString" was created before.
  SetTimeFormat(
    //        "%day%.%month%.%year% %hour%:%minute%:%second%,%millisecond%";
/** see
http://logging.apache.org/log4j/1.2/apidocs/org/apache/log4j/helpers/ISO8601DateFormat.html
*:"yyyy-MM-dd HH:mm:ss,SSS" for example "1999-11-27 15:49:37,459".*/
    "{year}-{month}-{day} {hour}:{minute}:{second},{millisecond}");
}

Log4jFormatter::~Log4jFormatter()
{
  // TODO Auto-generated destructor stub
}

/**@return use type "const char * const" because it has the same type as a
 *  string literal, so no cast is needed.*/
inline const char * Log4jFormatter::GetLogLevelAsString(
  enum LogLevel::MessageType messageType)
{
  switch(messageType)
  {
    case LogLevel::debug:
      return /*TU_Bln361095castToCharPtr*/ "DEBUG";
    case LogLevel::info:
      return /*TU_Bln361095castToCharPtr*/ "INFO";
    case LogLevel::warning:
      //Must NOT be "WARNING" else it was shown as level "FINE" in Otros
      //log file viewer
      return /*TU_Bln361095castToCharPtr*/ "WARN";
    case LogLevel::error:
      return /*TU_Bln361095castToCharPtr*/ "ERROR";
    //Unused, but if not handled: g++ warning
    case LogLevel::beyondLastLogMessageType:
    case LogLevel::success:
      break;
  }
  return /*TU_Bln361095castToCharPtr*/ "UNKNOWN";
}

}}///namespaces end
//TODO TU_Bln361095LoggerNmSpcEnd