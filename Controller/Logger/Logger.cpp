/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
//#if defined( _MSC_VER) 
//#include "StdAfx.h"
//#endif //#ifdef _MSC_VER

#include "Logger.hpp"  //important for wxWidgets 2.9: include windows.h AFTER
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
  m_trie.insert( (unsigned char*) cr_stdstr.c_str(), cr_stdstr.length() ) ;
}
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

Logger::Logger(
//  const std::set<std::string> & cr_stdsetstdstrExcludeFromLogging
  )
  //C++ style initialisation.
  :
    m_p_log_formatter(NULL),
    m_p_std_ofstream(NULL)
//  , m_p_stdsetstdstrExcludeFromLogging( gp_cpucontrolbase)
{
  CreateFormatter("",
    "%year%.%month%.%day%&nbsp;%hour%:%minute%:%second%s%millisecond%ms");
}

Logger::Logger( std::string & stdstrFilePath )
{
    //m_ofstream.open(stdstrFilePath.c_str() );
  m_stdsetLogClass.insert(Logger::sync) ;
}

Logger::~Logger()
{
  if( m_p_log_formatter )
  {
    m_p_log_formatter->WriteTrailer();
    delete m_p_log_formatter;
    m_p_log_formatter = NULL;
  }
//  LOGN("~Logger")
#ifndef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//  m_trie.FreeMemory() ;
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  delete m_p_std_ofstream ;
  //Set to NULL so the calling Log() evaluates the pointer address if it is
  // NULL.
  m_p_std_ofstream = NULL ;
//  LOGN("end of ~Logger")
}

I_LogFormatter * Logger::CreateFormatter(//BYTE type = 1
  const std::string & std_strType //= std::string("html")
  , const std::string & std_strLogTimeFormatString
  )
{
  if( m_p_log_formatter)
    delete m_p_log_formatter;
  if( //type == 1
      std_strType == "html"
    )
    m_p_log_formatter = new HTMLformatLogFileWriter(//m_p_std_ofstream
      this);
  else
    m_p_log_formatter = new I_LogFormatter(//m_p_std_ofstream
      this);

  if( m_p_log_formatter)
  {
    m_p_log_formatter->WriteHeader();
    m_p_log_formatter->SetTimeFormat(std_strLogTimeFormatString);
  }
  return m_p_log_formatter;
}

bool Logger::IsOpen()
{
  return m_p_std_ofstream //!= NULL
    && m_p_std_ofstream->is_open() ;
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

void Logger::Log(//ostream & ostr
    const std::vector<BYTE> & c_r_std_vec_by
    )
{
  //  if(r_stdstr.end().)
//Synchronization is not used in CPU controller logging.
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  //Protect access to the trie: if 2 or more threads access the
  // trie then an invalid array index for a trie level might be used?!
  //If the output is _not_ synchronized and 2 or more threads are
  // logging concurrently: the output may be mixed like:
  // "22010.8.10 2010.99h:824.min 1051 19491msad24hread ID:tC8296ntCP51os
  //  ter getting DOM implementationt("
//      m_critical_section_typeLogging.Enter() ;
#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE

  if(
    //Fastest evaluable condition at the beginning.
    m_p_std_ofstream &&
    //If NOT in the container.
  //Filtering is not used in CPU controller logging.
  #ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  //      m_stdsetstdstrExcludeFromLogging.find(r_stdstr) ==
  //      m_stdsetstdstrExcludeFromLogging.end()
    ! m_trie.exists_inline(
//      (unsigned char*) r_stdstr.c_str() ,
      c_r_std_vec_by
//      (WORD) r_stdstr.length( )
      ,
      false // allow prefix match: e.g. "hello" is prefix of "hello1"
      )
  //  )
  //if( //m_ofstream.good()
  &&
  #endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    m_p_std_ofstream->good()
    )
  {
    OutputTimeStampEtc_Inline(c_r_std_vec_by);

    //m_ofstream.flush() ;
    m_p_std_ofstream->flush() ;
//        #ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
//        m_critical_section_typeLogging.Leave() ;
//        #endif
    //TODO write into RAM for having 2 possibilties:
    //-truncate the log file to zero for every startup
    //-append to log file at every startup

    //->Write into RAM until the config file that determines which of these
    //2 possibilities to use is completely read.
    //If the config says: always append: simply delete the RAM buffer.
    //If the config says: always truncate:
    // 1. truncate the log file to zero
    // 2. write the RAM buffer contents ( that are the same as in
    //   log file written from startup till then)
    // 3. delete the RAM buffer.
    //buffer.add( ofstream.str() ) ;
//      #ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
  }
//#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
//      else
//        m_critical_section_typeLogging.Leave() ;
//#endif
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
//      m_critical_section_typeLogging.Leave() ;
#endif

//      #endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
}

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
  std::wstring & r_stdstr
  )
{
  if( //m_ofstream.good() 
      mp_ofstream && mp_ofstream->good() 
      )
  {
//    SYSTEMTIME m_systemtime ;
    //GetSystemTime( & m_systemtime); // gets current time in UTC / GMT? time zome
    ::GetLocalTime( & m_systemtime ); //gets the same time as the Windows clock.
    //m_ofstream << r_stdstr ;
    *mp_ofstream
        << m_systemtime.wYear
        << "." << m_systemtime.wMonth
        << "." << m_systemtime.wDay
        << " " << m_systemtime.wHour
        << "h:" << m_systemtime.wMinute
        << "min " << m_systemtime.wSecond
        << "s " << m_systemtime.wMilliseconds
        << "ms:" << r_stdstr.c_str() ;
    //m_ofstream.flush() ;
    mp_ofstream->flush() ;

    //TODO write into RAM for having 2 possibilties:
    //-truncate the log file to zero for every startup
    //-append to log file at every startup

    //->Write into RAM until the config file that determines which of these
    //2 possibilties to use is completely read.
    //If the config says: always append: simply delete the RAM buffer.
    //If the config says: always truncate:
    // 1. truncate the log file to zero
    // 2. write the RAM buffer contents ( that are the same as in
    //   log file written from startup till then)
    // 3. delete the RAM buffer.
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

bool Logger::OpenFile2( std::string & r_stdstrFilePath
  )
{
  m_std_strLogFilePath = r_stdstrFilePath;
    //When the ofstream was not dynamically created (=on the heap)
    //the was no content within the file even when there was at least
    //1 output via the "<<" operator and this program was terminated
    //(=contents should have been written then).
    //Maybe this was due to a wrong thread/ process affinity for the
    //ofstream object.
    //So I create the ofstream object dynamically.
    if( ! m_p_std_ofstream )
      m_p_std_ofstream = new std::ofstream ;
    //m_ofstream.open(
    m_p_std_ofstream->open(
      r_stdstrFilePath.c_str()
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
    if( bFileIsOpen )
      CreateFormatter("",
        "%year%.%month%.%day%&nbsp;%hour%:%minute%:%second%s%millisecond%ms");
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
    GetStdString(r_stdtstrFilePath) ) ;
  return OpenFile2( stdstr ) ;
}
#endif //#ifdef COMPILE_LOGGER_WITH_TSTRING_SUPPORT

int Logger::RenameFile(const std::string & cr_std_strFilePath)
{
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  //Sync with other code accessing the ofstream.
  m_critical_section_typeLogging.Enter();
#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  if( m_p_std_ofstream )
  {
    m_p_std_ofstream->close();
    //from http://www.cplusplus.com/reference/clibrary/cstdio/rename/
    // http://msdn.microsoft.com/en-us/library/zw5t957f%28v=vs.71%29.aspx
    int result = rename
        //_trename
      ( //oldname
      m_std_strLogFilePath.c_str(), cr_std_strFilePath.c_str() //newname
      );
    if( result == 0)
    {
      m_std_strLogFilePath = cr_std_strFilePath;
      m_p_std_ofstream->open( m_std_strLogFilePath.c_str(),
        //ate = AT End
        //see http://www.cplusplus.com/reference/iostream/ofstream/open/:
        //(at end) Set the stream's position indicator to the end of the stream on opening.
        std::ios_base::ate );
    }
    return result;
  }
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  m_critical_section_typeLogging.Leave();
#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  return -1;
}

void Logger::TruncateFileToZeroAndRewrite()
{

}
