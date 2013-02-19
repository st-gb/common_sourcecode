/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
//#if defined( _MSC_VER) 
//#include "StdAfx.h"
//#endif //#ifdef _MSC_VER

#include "Logger.hpp"  //important for wxWidgets 2.9: include windows.h AFTER
#include "LogLevel.hpp" //LogLevel::MessageType
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)

//If MS compiler etc.
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__)
  //#include <Windows.h> //for SYSTEMTIME
  //Use "windows.h" for g++ because the case matters.
  #include <windows.h> //for SYSTEMTIME
#endif
//#include <preprocessor_macros/logging_preprocessor_macros.h>
//#include <Controller/tchar_conversion.h> //GetCharPointer()
//#include <Controller/character_string/stdtstr.hpp> //GetStdString(...)

Logger::Logger(
//  const std::set<std::string> & cr_stdsetstdstrExcludeFromLogging
  )
{
//  CreateTextFormatter();
  if( LogLevel::s_nodetrieLogLevelStringToNumber.size() == 0)
    LogLevel::CreateLogLevelStringToNumberMapping();
}

Logger::~Logger()
{
  std::vector<FormattedLogEntryProcessor *>::reverse_iterator
    rev_iterFormattedLogEntryProcessors =
    m_formattedLogEntryProcessors.rbegin();
  while( rev_iterFormattedLogEntryProcessors !=
      m_formattedLogEntryProcessors.rend() )
  {
    delete * rev_iterFormattedLogEntryProcessors;
    ++ rev_iterFormattedLogEntryProcessors;
  }
}

#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
void Logger::AddExcludeFromLogging(
  const std::string & cr_stdstr )
{
  static std::vector<FormattedLogEntryProcessor *>::const_iterator
    c_iterFormattedLogEntryProcessors;
  c_iterFormattedLogEntryProcessors = m_formattedLogEntryProcessors.begin();
  while( c_iterFormattedLogEntryProcessors !=
      m_formattedLogEntryProcessors.end() )
  {
    NodeTrie<BYTE> & trie = ( * c_iterFormattedLogEntryProcessors)->GetTrie();
    trie.//insert
      insert_inline( (unsigned char*) cr_stdstr.c_str(), cr_stdstr.length()
        , FormattedLogEntryProcessor::string_end) ;
    ++ c_iterFormattedLogEntryProcessors;
  }
}
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

/** Do not call this method thread-unsafe -> enter a critical section before
 * calling it */
DWORD Logger::Log(//ostream & ostr
  const std::string & r_stdstrMessage,
  enum LogLevel::MessageType messageType /*= LogLevel::info*/,
  const char * const prettyFunctionFormattedFunctionName /*= NULL*/
  )
{
  return Log_inline(r_stdstrMessage, messageType,
    prettyFunctionFormattedFunctionName);
}

//void Logger::Log(//ostream & ostr
//    std::ostrstream & r_ostrstream 
//    )
//{
//    //std::stringstream s;
//    //s.
//    if( m_ofstream.good() )
//    {
//      //Must set this, else text may follow after the string we want.
//      //I had program crashes with the following method:
//      //pch[r_ostrstream.pcount()] = '\0' ;
//      //r_ostrstream.ends();
//      r_ostrstream.put('\0'); //the same as "ends()" does.
//      char *pch = r_ostrstream.str() ;
//        m_ofstream << pch ;
//        m_ofstream.flush() ;
//    }
//}

//void Logger::Log(//ostream & ostr
//    std::string & r_stdstr
//    )
//{
//
//}

//void Logger::Log(//ostream & ostr
//    std::string & r_stdstr
//    , WORD wType
//    )
//{
////  if( mp_model )
////  {
////    if( mp_model->
////        )
////  }
//  if( m_stdsetLogClass.find(wType) != m_stdsetLogClass.end() )
//    Log(r_stdstr) ;
//}

//void Logger::Log(//ostream & ostr
//  const char * p_ch
//  )
//{
//  if( //m_ofstream.good()
//    m_p_std_ofstream && m_p_std_ofstream->good() )
//  {
//    //m_ofstream << p_ch ;
//    * m_p_std_ofstream //<< " char * "
//        << p_ch ;
//    //m_ofstream.flush() ;
//    m_p_std_ofstream->flush() ;
//  }
//}
