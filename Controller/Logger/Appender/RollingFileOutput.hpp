/*
 * RollingFileOutput.hpp
 *
 *  Created on: 07.02.2013
 *      Author: Stefan
 */

#ifndef ROLLINGFILEOUTPUT_HPP_
#define ROLLINGFILEOUTPUT_HPP_

//class RollingFileOutput
//{
//public:
//  RollingFileOutput();
//  virtual
//  ~RollingFileOutput();
//};
#include "FormattedLogEntryProcessor.hpp"

class RollingFileOutput
  : public FormattedLogEntryProcessor
{
private:
  bool lowerFileName;
  std::string m_actualFilePath;
  unsigned m_maxNumberOfEntries;
  unsigned m_numberOfEntries;
public:
  RollingFileOutput(
    Logger & logger,
    I_LogEntryOutputter * p_outputhandler,
    I_LogFormatter * p_log_formatter,
    unsigned maxNumberOfEntries,
    enum LogLevel::MessageType logLevel
    )
    :
    FormattedLogEntryProcessor(
      logger,
      p_outputhandler,
      //    m_nodetrieLogLevelStringToNumber(255),
      p_log_formatter,
      logLevel)
//    #ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//      , m_trie(255, no_string_end)
//    #endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    ,
    lowerFileName(true),
    m_maxNumberOfEntries(maxNumberOfEntries),
    m_numberOfEntries(0)
  {
  }
  RollingFileOutput(
    Logger & logger,
    const std::string & filePath,
    I_LogEntryOutputter * p_outputhandler,
    const std::string & format,
    unsigned numberOfEntries,
    enum LogLevel::MessageType logLevel
    )
    :
    FormattedLogEntryProcessor(
      logger,
      filePath,
      p_outputhandler,
      //    m_nodetrieLogLevelStringToNumber(255),
      format,
      logLevel),
//    #ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//      , m_trie(255, no_string_end)
//    #endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    lowerFileName(true),
    m_maxNumberOfEntries(numberOfEntries),
    m_numberOfEntries(0)
  {
  }
  virtual ~RollingFileOutput() {};

  void ReOpenLogFile()
  {
    m_p_log_formatter->WriteTrailer();
    m_p_outputhandler->Close();
    Open(m_actualFilePath);
    m_p_log_formatter->WriteHeader();
  }

  bool GetActualFilePath(std::string & str);
  bool Open(std::string & actualFilePath);

  unsigned Log(//ostream & ostr
//    const std::string & r_stdstrMessage,
    const LogFileEntry & logfileentry,
    enum LogLevel::MessageType messageType =
      LogLevel::info,
    const char * const prettyFunctionFormattedFunctionName = NULL
    ) const
  {
//    else
//      ++ ( (RollingFileOutput*) this)->m_numberOfEntries;
      //      EnterCritSec();
      if( //Fastest evaluable condition at first.
        //m_p_std_ofstream &&
          m_p_std_ostream && m_p_log_formatter
        )
      {
        if(
        #ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
          prettyFunctionFormattedFunctionName &&
          FunctionIsNotFiltered(/* *logfileentry.p_std_strMessage*/
            prettyFunctionFormattedFunctionName,
            strlen(prettyFunctionFormattedFunctionName) )
           &&
        #endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//          m_p_std_ofstream->good()
          m_p_std_ostream->good()
          )
        {
          if( ++ ( (RollingFileOutput*) this)->m_numberOfEntries >
            m_maxNumberOfEntries)
          {
            ( (RollingFileOutput*) this)->ReOpenLogFile();
            ( (RollingFileOutput*) this)->m_numberOfEntries = 1;
          }
          //TODO make rolling log files possible
//          if( m_bRolling && m_numLogEntries > m_maxNumLogEntries )
//
//          if(m_numFiles > 1)
//          {
//            TruncateFileSizeToZero();
//          }
//          return OutputTimeStampEtc_Inline(r_stdstrMessage, messageType,
//            prettyFunctionFormattedFunctionName);
          m_p_log_formatter->WriteLogFileEntry(logfileentry, messageType,
            prettyFunctionFormattedFunctionName);
          return m_p_outputhandler->DoOutput();
          //m_ofstream.flush() ;
  //        POSSIBLY_LEAVE_CRIT_SEC
  //        Ideas();
        }
      }
//      else
//        m_std_vecLogMessage.push_back( LogFileEntry() )
//#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
//      else
//        m_critical_section_typeLogging.Leave() ;
//#endif
//      POSSIBLY_LEAVE_CRIT_SEC
      return UINT_MAX;
      //    return 0;
//    }
  }//Log(...)
};

#endif /* ROLLINGFILEOUTPUT_HPP_ */
