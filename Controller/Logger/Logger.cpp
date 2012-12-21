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
#include "HTMLlogFormatter.hpp" //class HTMLlogFormatter::HTMLlogFormatter(...)
#include "LogLevel.hpp" //LogLevel::MessageType
#include <Controller/GetLastErrorCode.hpp>

//If MS compiler etc.
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__)
  //#include <Windows.h> //for SYSTEMTIME
  //Use "windows.h" for g++ because the case matters.
  #include <windows.h> //for SYSTEMTIME
#endif
//#include <preprocessor_macros/logging_preprocessor_macros.h>
//#include <Controller/tchar_conversion.h> //GetCharPointer()
//#include <Controller/character_string/stdtstr.hpp> //GetStdString(...)
#include <fstream> //for class std::ofstream

#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
void Logger::AddExcludeFromLogging(const std::string & cr_stdstr )
{
  m_trie.//insert
    insert_inline( (unsigned char*) cr_stdstr.c_str(), cr_stdstr.length()
      , string_end) ;
}
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

Logger::Logger(
//  const std::set<std::string> & cr_stdsetstdstrExcludeFromLogging
  )
  //C++ style initialisation.
  :
//    m_nodetrieLogLevelStringToNumber(255),
#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    m_trie(255),
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    m_logLevel(LogLevel:://warning),
      info),
    m_p_log_formatter(NULL),
    m_p_std_ofstream(NULL),
    m_p_std_ostream(NULL)
//  , m_p_stdsetstdstrExcludeFromLogging( gp_cpucontrolbase)
{
//  CreateTextFormatter();
  if( LogLevel::s_nodetrieLogLevelStringToNumber.size() == 0)
    LogLevel::CreateLogLevelStringToNumberMapping();
}

Logger::Logger( std::string & stdstrFilePath )
#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  : m_trie(255)
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
{
    //m_ofstream.open(stdstrFilePath.c_str() );
//  m_stdsetLogClass.insert(Logger::sync) ;
}

Logger::~Logger()
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
//  LOGN("~Logger")
#ifndef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//  m_trie.FreeMemory() ;
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  if( m_p_std_ofstream)
    delete m_p_std_ofstream ;
  //Set to NULL so the calling Log() evaluates the pointer address if it is
  // NULL.
  m_p_std_ofstream = NULL ;
  m_p_std_ostream = NULL;
//  LOGN("end of ~Logger")
}

I_LogFormatter * Logger::CreateFormatter(//BYTE type = 1
  //const std::string & std_strType //= std::string("html")
  const char * c_p_chType //= "html"
  , const std::string & std_strLogTimeFormatString
  //const char * c_p_chLogTimeFormatString
  )
{
  if( m_p_log_formatter)
    delete m_p_log_formatter;
  if( //type == 1
      //std_strType == "html"
      strcmp("html", c_p_chType) == 0
    )
    m_p_log_formatter = new HTMLlogFormatter(//m_p_std_ofstream
      this);
  else
    m_p_log_formatter = new I_LogFormatter(//m_p_std_ofstream
      this);

  if( m_p_log_formatter)
  {
//    m_p_log_formatter->SetStdOstream( & GetStdOstream() );
    m_p_log_formatter->WriteHeader();
    m_p_log_formatter->SetTimeFormat(std_strLogTimeFormatString);
  }
  return m_p_log_formatter;
}

bool Logger::IsOpen()
{
  bool isOpen =
  m_p_std_ofstream //!= NULL
    && m_p_std_ofstream->is_open() ;
  return isOpen;
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

#ifdef COMPILE_WITH_WSTRING
void Logger::LogW(//ostream & ostr
  const std::wstring & c_r_std_wstr
  )
{
  if( //m_ofstream.good() 
      mp_ofstream && mp_ofstream->good() 
      )
  {
    outputLogFilePrefix(mp_ofstream);
    * mp_ofstream << c_r_std_wstr;
    //m_ofstream.flush() ;
    mp_ofstream->flush() ;

    Ideas();
    //buffer.add( ofstream.str() ) ;
  }
}
#endif //#ifdef COMPILE_WITH_WSTRING

void Logger::Log(//ostream & ostr
  const char * p_ch
  )
{
  if( //m_ofstream.good()
    m_p_std_ofstream && m_p_std_ofstream->good() )
  {
    //m_ofstream << p_ch ;
    * m_p_std_ofstream //<< " char * "
        << p_ch ;
    //m_ofstream.flush() ;
    m_p_std_ofstream->flush() ;
  }
}

/** ANSI version of OpenFile */
bool Logger::OpenFileA( const std::string & c_r_stdstrFilePath, bool bRolling)
{
//  m_bRolling = bRolling;
  m_std_strLogFilePath = c_r_stdstrFilePath;
  bool bFileIsOpen =
//#ifdef _WIN32
//  OpenFlushingFile(c_r_stdstrFilePath);
//#else
  SetStdOstream(c_r_stdstrFilePath);
//  GetStdOstream();
//#endif
  if( bFileIsOpen )
    if( m_p_log_formatter == NULL )
//    CreateFormatter("",
//      "%year%.%month%.%day% %hour%:%minute%:%second%s%millisecond%ms ");
      CreateTextFormatter();
  return bFileIsOpen;
  //m_ofstream << "File Opened" ;
  //*mp_ofstream << "File Opened" ;
  //m_ofstream.close() ;
  //m_ofstream.write(arch,6) ;
  //m_ofstream.flush() ;
}

#ifdef COMPILE_LOGGER_WITH_TSTRING_SUPPORT
//void 
bool Logger::OpenFile( //std::string & r_stdstrFilePath
  std::tstring & r_stdtstrFilePath)
{
  std::string stdstr( //GetCharPointer(r_stdtstrFilePath.c_str() ) ) ;
    GetStdString_Inline(r_stdtstrFilePath) ) ;
  return OpenFileA( stdstr ) ;
}
#endif //#ifdef COMPILE_LOGGER_WITH_TSTRING_SUPPORT

inline bool Logger::SetStdOstream(const std::string & c_r_stdstrFilePath)
{
  //When the ofstream was not dynamically created (=on the heap)
  //the was no content within the file even when there was at least
  //1 output via the "<<" operator and this program was terminated
  //(=contents should have been written then).
  //Maybe this was due to a wrong thread/ process affinity for the
  //ofstream object.
  //So I create the ofstream object dynamically.
  if( ! m_p_std_ofstream )
    m_p_std_ofstream = new std::ofstream ;
    //std::basic_ofstream<WCHAR>;
  //m_ofstream.open(
  m_p_std_ofstream->open(
    c_r_stdstrFilePath.c_str()
    //GetCharPointer(r_stdtstrFilePath.c_str() )
      //, std::ios_base::out | std::ios_base::trunc
      );
#ifdef _DEBUG
//    bool bOfstreamIsGood = mp_ofstream->good() ;
#endif
  bool bFileIsOpen = m_p_std_ofstream->//good() ;
    //TODO "is_open" returned true
    //if no entry in file system rights was defined for user this program ran
    //under in NTFS file system running on Windows. But no file was created.
    //
    is_open();
  if( bFileIsOpen)
    m_p_std_ostream = m_p_std_ofstream;
  return bFileIsOpen;
}

int Logger::RenameFileThreadUnsafe(const std::string & cr_std_strFilePath)
{
  int retVal = -1;
  if( m_p_std_ofstream )
  {
    m_p_std_ofstream->close();
    //Must delete before renaming to this name.
    retVal = remove ( cr_std_strFilePath.c_str() );
    //http://www.cplusplus.com/reference/clibrary/cstdio/remove/:
    //"If the file is successfully deleted, a zero value is returned."
//    if( ! retVal )
    {
      //from http://www.cplusplus.com/reference/clibrary/cstdio/rename/
      // http://msdn.microsoft.com/en-us/library/zw5t957f%28v=vs.71%29.aspx
      retVal = rename
          //_trename
        ( //oldname
        m_std_strLogFilePath.c_str(), cr_std_strFilePath.c_str() //newname
        );
      retVal = OperatingSystem::GetLastErrorCode();
      //"If the file is successfully renamed, a zero value is returned."
      if( retVal == 0)
      {
        m_std_strLogFilePath = cr_std_strFilePath;
        m_p_std_ofstream->open( m_std_strLogFilePath.c_str(),
          //ate = AT End
          //see http://www.cplusplus.com/reference/iostream/ofstream/open/:
          //(at end) Set the stream's position indicator to the end of the stream on opening.
          std::ios_base::ate );
      }
    }
//    else
//      retVal = ::LocalLanguageMessageAndErrorCodeA();
  }
  return retVal;
}

int Logger::RenameFileThreadSafe(const std::string & cr_std_strFilePath)
{
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  //Sync with other code accessing the ofstream.
  m_critical_section_typeLogging.Enter();
#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  int i = RenameFileThreadUnsafe(cr_std_strFilePath);
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  m_critical_section_typeLogging.Leave();
#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  return i;
}

void Logger::TruncateFileToZeroAndRewrite()
{

}
