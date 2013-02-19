/*
 * AppendingFileOutput.hpp
 *
 *  Created on: 08.02.2013
 *      Author: Stefan
 */

#ifndef APPENDINGFILEOUTPUT_HPP_
#define APPENDINGFILEOUTPUT_HPP_

#include "FormattedLogEntryProcessor.hpp"

//class AppendingFileOutput
//{
//public:
//  AppendingFileOutput();
//  virtual
//  ~AppendingFileOutput();
//};

class AppendingFileOutput
  : public FormattedLogEntryProcessor
{
public:
  I_LogFormatter * m_p_formatter;
//  I_LogEntryOutputter * m_p_logentryoutputter;
  AppendingFileOutput(
    Logger & logger,
    I_LogEntryOutputter * p_outputhandler,
    I_LogFormatter * p_log_formatter,
    enum LogLevel::MessageType logLevel
    )
    :
    FormattedLogEntryProcessor(
      logger,
//      filePath,
      p_outputhandler,
      //    m_nodetrieLogLevelStringToNumber(255),
      p_log_formatter,
      logLevel)
//      m_filePath(filePath)//,
//      m_p_formatter(& formatter),
//      m_p_logentryoutputter(& p_outputhandler)
  {
//    m_p_outputhandler->SetStdOstream(filePath);
  }
  AppendingFileOutput(
    Logger & logger,
    const std::string & filePath,
    I_LogEntryOutputter * p_outputhandler,
    const std::string & format,
    enum LogLevel::MessageType logLevel
    )
    :
    FormattedLogEntryProcessor(
      logger,
      filePath,
      p_outputhandler,
      //    m_nodetrieLogLevelStringToNumber(255),
      format,
      logLevel)
//      m_filePath(filePath)//,
//      m_p_formatter(& formatter),
//      m_p_logentryoutputter(& p_outputhandler)
  {
//    m_p_outputhandler->SetStdOstream(filePath);
  }
  ~AppendingFileOutput() {}
  bool Open();
  unsigned Log(//ostream & ostr
//    const std::string & r_stdstrMessage,
    const LogFileEntry & logfileentry,
    enum LogLevel::MessageType messageType =
      LogLevel::info,
    const char * const prettyFunctionFormattedFunctionName = NULL
    ) const
  {
    m_p_formatter->WriteLogFileEntry(logfileentry, messageType,
      prettyFunctionFormattedFunctionName);
    return m_p_outputhandler->DoOutput();
  }
};

#endif /* APPENDINGFILEOUTPUT_HPP_ */
