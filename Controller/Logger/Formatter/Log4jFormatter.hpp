/**(c)from 2012:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
 * Created 17 Dec 2012 by Stefan Gebauer,TU Berlin matriculation number 361095*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
#ifdef TU_Bln361095PrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
#pragma once
#endif
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095LoggerLog4jFormatter_hpp
#define TU_Bln361095LoggerLog4jFormatter_hpp

///_This_ repository's header files:
#include "I_LogFormatter.hpp"

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
//GetClassName(...), GetFunctionName(...)
#include <compiler/current_function.hpp>
//TU_Bln361095::charStr::convertToStdString(...)
#include <dataType/charStr/convertFromAndToStdString.hpp>
//#include <Controller/character_string/getUTF8string.hpp>

namespace TU_Bln361095{namespace Logger{
/** Class that aims to write Log4J compliant log files.*/
class Log4jFormatter
  : public I_LogFormatter
{
public:
  Log4jFormatter(const /*Logger * p_logger*/
//        I_LogEntryOutputter * p_outputhandler
    FormattedLogEntryProcessor *);
  virtual
  ~Log4jFormatter();

  /** @see http://logging.apache.org/log4j/1.2/apidocs/org/apache/log4j/Level.html
   * All strings must contain <= 5 characters for log file viewers? */
  //inline
    char * GetLogLevelAsString(enum LogLevel::MessageType messageType);

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
    enum LogLevel::MessageType messageType = LogLevel::info,
    const char * const prettyFunctionFormattedFunctionName = NULL
    )
  {
//    static std::string std_strTime;
    GetTimeAsString(logfileentry /*, std_strTime*/ );
//        char * threadName = logfileentry.p_std_strThreadName ?
//          << "[" << logfileentry.p_std_strThreadName << "] " :
//          << "[" "Thread-"          << logfileentry.threadID << "] ";
    static std::string std_strThreadName;
    static const std::string * p_std_strThreadName;
    static const char * p_chThreadName;
    p_std_strThreadName = logfileentry.p_std_strThreadName;
    if( p_std_strThreadName)
    {
      //p_chThreadName = p_std_strThreadName->c_str();
      std_strThreadName = * p_std_strThreadName + "-" +
        TU_Bln361095::charStr::convertToStdString(logfileentry.threadID);
      p_chThreadName = std_strThreadName.c_str();
    }
    else
    {
      std_strThreadName = "Thread-" + TU_Bln361095::charStr::
        convertToStdString(logfileentry.threadID);
      p_chThreadName = std_strThreadName.c_str();
    }
    if( prettyFunctionFormattedFunctionName)
    {
      //TODO enable UTF-8 logging?
      //std::string std_strUTF8 = getUTF8string(* logfileentry.p_std_strMessage);
      * m_p_std_ostream
        << m_p_chFormattedTimeString << " "
        << GetLogLevelAsString(messageType) << " "
//            << logfileentry.p_std_strThreadName ?
//              << "[" << logfileentry.p_std_strThreadName << "] " :
//              << "[" "Thread-"
//              << logfileentry.threadID << "] "
        << "[" << p_chThreadName << "] "
        //  e.g. "[Thread-1]"
        << PrettyFunctionFormattedFunctionSignature::GetClassName(//__PRETTY_FUNCTION__
          prettyFunctionFormattedFunctionName) << " "
        << PrettyFunctionFormattedFunctionSignature::GetFunctionName(//__PRETTY_FUNCTION__
          prettyFunctionFormattedFunctionName) << " "
        << * logfileentry.p_std_strMessage //<< std::endl
//          << " thread ID:" << logfileentry.threadID << " "
  //      << "\n"
        ;
    }
  }
};
}}///namespaces end
#endif///TU_Bln361095LoggerLog4jFormatter_hpp