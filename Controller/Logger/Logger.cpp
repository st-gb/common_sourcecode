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

#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
void Logger::AddExcludeFromLogging(const std::string & cr_stdstr )
{
  m_trie.insert( (unsigned char*) cr_stdstr.c_str(), cr_stdstr.length() ) ;
}
#endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB

Logger::Logger(
//  const std::set<std::string> & cr_stdsetstdstrExcludeFromLogging
  )
  //C++ style initialisation.
  : mp_ofstream(NULL)
//  , m_p_stdsetstdstrExcludeFromLogging( gp_cpucontrolbase)
  {}

Logger::Logger( std::string & stdstrFilePath )
{
    //m_ofstream.open(stdstrFilePath.c_str() );
  m_stdsetLogClass.insert(Logger::sync) ;
}

Logger::~Logger()
{
//  LOGN("~Logger")
#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
//  m_trie.FreeMemory() ;
#endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
  delete mp_ofstream ;
  //Set to NULL so the calling Log() evaluates the pointer address if it is
  // NULL.
  mp_ofstream = NULL ;
//  LOGN("end of ~Logger")
}

bool Logger::IsOpen()
{
  return mp_ofstream //!= NULL
    && mp_ofstream->is_open() ;
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
#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
  //Protect access to the trie: if 2 or more threads access the
  // trie then an invalid array index for a trie level might be used?!
  //If the output is _not_ synchronized and 2 or more threads are
  // logging concurrently: the output may be mixed like:
  // "22010.8.10 2010.99h:824.min 1051 19491msad24hread ID:tC8296ntCP51os
  //  ter getting DOM implementationt("
//      m_critical_section_typeLogging.Enter() ;
#endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB

  if(
    //Fastest evaluable condition at the beginning.
    mp_ofstream &&
    //If NOT in the container.
  //Filtering is not used in CPU controller logging.
  #ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
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
#endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
    mp_ofstream->good()
    )
  {
    OutputTimeStampEtc_Inline(c_r_std_vec_by);

    //m_ofstream.flush() ;
    mp_ofstream->flush() ;
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
//#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
//      else
//        m_critical_section_typeLogging.Leave() ;
//#endif
#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
//      m_critical_section_typeLogging.Leave() ;
#endif

//      #endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
}

void Logger::Log(//ostream & ostr
    std::string & r_stdstr
    , WORD wType
    )
{
//  if( mp_model )
//  {
//    if( mp_model->
//        )
//  }
  if( m_stdsetLogClass.find(wType) != m_stdsetLogClass.end() )
    Log(r_stdstr) ;
}

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
    char * p_ch
    )
{
    if( //m_ofstream.good() 
       mp_ofstream && mp_ofstream->good() )
    {
        //m_ofstream << p_ch ;
        *mp_ofstream //<< " char * " 
            << p_ch ;
        //m_ofstream.flush() ;
        mp_ofstream->flush() ;
    }
}

bool Logger::OpenFile2( std::string & r_stdstrFilePath
  )
{
    //char arch [10] = "File\r\n" ;
    //When the ofstream was not dynamically created (=on the heap)
    //the was no content within the file even when there was at least
    //1 output via the "<<" operator and this program was terminated
    //(=contents should have been written then).
    //Maybe this was due to a wrong thread/ process affinity for the
    //ofstream object.
    //So I create the ofstream object dynamically.
    if( ! mp_ofstream )
        mp_ofstream = new std::ofstream ;
    //m_ofstream.open(
    mp_ofstream->open(
      r_stdstrFilePath.c_str()
      //GetCharPointer(r_stdtstrFilePath.c_str() )
        //"C:\\Temp\\GriffinSvc_log.txt"
        //, std::ios_base::out | std::ios_base::trunc
        );
#ifdef _DEBUG
//    bool bOfstreamIsGood = mp_ofstream->good() ;
#endif
    return mp_ofstream->good() ;
    //std::ofstream ofstreamTest;
    //ofstreamTest.open( "C:\\Temp\\GriffinSvc_text.txt" );
    //ofstreamTest << "hhh bla" ;
    //ofstreamTest << r_stdstrFilePath << " is " <<
    //    ( m_ofstream.is_open() ? "" : " NOT " ) << "open\n" ;
    //m_ofstream << "File Opened" ;
    //*mp_ofstream << "File Opened" ;
    //m_ofstream.close() ;
    //m_ofstream.write(arch,6) ;
    //m_ofstream.flush() ;
}

#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
//void 
bool Logger::OpenFile( //std::string & r_stdstrFilePath
  std::tstring & r_stdtstrFilePath)
{
  std::string stdstr( //GetCharPointer(r_stdtstrFilePath.c_str() ) ) ;
    GetStdString(r_stdtstrFilePath) ) ;
  return OpenFile2( stdstr ) ;
}
#endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB

void Logger::TruncateFileToZeroAndRewrite()
{

}
