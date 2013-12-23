/*
 * FormattedLogEntryProcessor.cpp
 *
 *  Created on: 07.02.2013
 *      Author: Stefan
 */

#include "FormattedLogEntryProcessor.hpp"
#include "../Formatter/HTMLlogFormatter.hpp" //class HTMLlogFormatter::HTMLlogFormatter(...)
#include "../Formatter/Log4jFormatter.hpp" //class Log4jFormatter::(...)
#include "../Logger.hpp"

FormattedLogEntryProcessor::FormattedLogEntryProcessor(
  Logger & logger,
  I_LogEntryOutputter * p_outputhandler,
  I_LogFormatter * p_log_formatter,
  enum LogLevel::MessageType logLevel
  )
  :
  m_p_logfileentry(& logger.m_logfileentry),
  m_p_outputhandler(p_outputhandler),
  m_p_log_formatter(p_log_formatter),
  m_p_std_ostream(NULL),
  //    m_nodetrieLogLevelStringToNumber(255),
//  m_p_log_formatter(NULL),
#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  m_trie(255, no_string_end),
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  m_logLevel(logLevel)
{
  if(p_outputhandler && m_p_log_formatter)
    m_p_log_formatter->Init(p_outputhandler->GetStdOstream() );
}

FormattedLogEntryProcessor::FormattedLogEntryProcessor(
  Logger & logger,
  const std::string & filePath,
  I_LogEntryOutputter * p_outputhandler,
  const std::string & format,
  enum LogLevel::MessageType logLevel
  )
  :
  m_filePath(filePath),
  m_p_logfileentry(& logger.m_logfileentry),
  m_p_outputhandler(p_outputhandler),
  //    m_nodetrieLogLevelStringToNumber(255),
  m_p_log_formatter(NULL),
  m_p_std_ostream(NULL),
#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  m_trie(255, no_string_end),
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  m_logLevel(logLevel)
{
  CreateFormatter(format.c_str() );
//  if( format == "txt" )
//  {
//    /*I_LogFormatter * p_formatter =*/ CreateTextFormatter();
////    if( m_p_log_formatter )
////      m_p_log_formatter->SetAppender(this);
//  }
}

FormattedLogEntryProcessor::~FormattedLogEntryProcessor()
{
  if( m_p_log_formatter )
  {
    m_p_log_formatter->WriteTrailer();
    //Write (flush) trailer to output.
    //TODO causes "::Logger::WriteToFile" to be and not the actual type's
    // "WriteToFile" to be called.
//    WriteToFile();
    delete m_p_log_formatter;
    m_p_log_formatter = NULL;
  }
}


#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
void FormattedLogEntryProcessor::AddExcludeFromLogging(
  const std::string & cr_stdstr )
{
  m_trie.//insert
    insert_inline( (unsigned char*) cr_stdstr.c_str(), cr_stdstr.length()
      , string_end) ;
}
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

I_LogFormatter * FormattedLogEntryProcessor::CreateFormatter(//BYTE type = 1
  //const std::string & std_strType //= std::string("html")
  const char * c_p_chType //= "html"
  , const std::string & std_strLogTimeFormatString
  //const char * c_p_chLogTimeFormatString
  )
{
#if defined(__linux__) && !defined(_DEBUG)
  #define _DEBUG
#endif
#ifdef _DEBUG
  /*NodeTrie::size_type*/ unsigned numberOfNodesAfterDelete;
#endif //#ifdef _DEBUG
  if( m_p_log_formatter)
  {
#ifdef _DEBUG
    /*NodeTrie::size_type*/ unsigned numberOfNodesAfterDelete = m_p_log_formatter->
      DeleteTimePlaceHolderToLogFileEntryMemberNodeTrie();
#endif //#ifdef _DEBUG
    delete m_p_log_formatter;
  }
//  unsigned numberOfNodesAfterDelete = m_p_log_formatter->
//    GetNumberOfTimePlaceHolderToLogFileEntryMemberNodes();
  if( //type == 1
      //std_strType == "html"
      strcmp("html", c_p_chType) == 0
    )
    m_p_log_formatter = new HTMLlogFormatter(//m_p_std_ofstream
      this);
  else if(strcmp("log4j", c_p_chType) == 0)
    m_p_log_formatter = new CSS::LogFormatter::Log4jFormatter(//m_p_std_ofstream
      this);
  else
    m_p_log_formatter = new I_LogFormatter(//m_p_std_ofstream
      this);
  if( m_p_log_formatter)
  {
#ifdef ___linux___
    (std::string &) std_strLogTimeFormatString += "{microsecond}us";
#endif
//    m_p_log_formatter->Init( GetStdOstream(), & std_strLogTimeFormatString);
#ifdef _DEBUG
//  LOGN_INFO("m_dwNumberOfNodes for PlaceHolderToLogFileEntryMember trie:"
//    << numberOfNodesAfterDelete )
#endif //#ifdef _DEBUG
#ifdef __linux__
  #undef _DEBUG
#endif
  }
  return m_p_log_formatter;
}

//bool FormattedLogEntryProcessor::GetActualFilePath(std::string & str)
//{
//  str = m_filePath;
//  return true;
//}

bool FormattedLogEntryProcessor::Open(std::string & actualFilePath)
{
  bool bOpen = false;
  if( GetActualFilePath(actualFilePath) )
  {
    bOpen = m_p_outputhandler->OpenA(actualFilePath );
    if( bOpen )
    {
      m_p_std_ostream = m_p_outputhandler->GetStdOstream();
      if( m_p_log_formatter)
      {
        m_p_log_formatter->SetStdOstream(m_p_std_ostream);
      }
    }
  }
  return bOpen;
}

void FormattedLogEntryProcessor::SetFormatter(I_LogFormatter * p_logformatter)
{
  if( m_p_log_formatter )
    delete m_p_log_formatter;
  m_p_log_formatter = p_logformatter;
  //m_p_log_formatter->Init(GetStdOstream() );
  if(m_p_outputhandler && m_p_log_formatter)
    m_p_log_formatter->Init(m_p_outputhandler->GetStdOstream() );

}

std::ostream & //VoltageAndFreq::
  operator << (std::ostream & std_ostream
  ,const FormattedLogEntryProcessor & formattedLogEntryProcessor
  ) //const
{
//    std::ostream std_ostream;
  std_ostream << "log level" << formattedLogEntryProcessor.m_logLevel <<
    "; file path:" << formattedLogEntryProcessor.m_filePath << ";";
  return std_ostream;
}
