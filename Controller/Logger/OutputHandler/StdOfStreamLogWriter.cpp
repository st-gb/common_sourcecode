/*
 * StdOfStreamLogWriter.cpp
 *
 *  Created on: 08.02.2013
 *      Author: Stefan
 */

#include "StdOfStreamLogWriter.hpp"
//#ifdef _WIN32
//  #include <windows.h> //GetLastError()
//#else
  #include <Controller/GetLastErrorCode.hpp>//OperatingSystem::GetLastErrorCode()
  #include <Controller/GetErrorMessageFromLastErrorCode.hpp>
  /** Class "LogFileAccessException" */
  #include <Controller/Logger/LogFileAccessException.hpp>
//#endif

StdOfStreamLogWriter::StdOfStreamLogWriter()
//C++ style initialisation.
:
  m_p_std_ofstream(NULL)//,
//  I_LogEntryOutputter(p_std_ostream)
//  , m_p_stdsetstdstrExcludeFromLogging( gp_cpucontrolbase)
{
}

StdOfStreamLogWriter::~StdOfStreamLogWriter()
{
  //  LOGN("~Logger")
  #ifndef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  //  m_trie.FreeMemory() ;
  #endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    if( m_p_std_ofstream)
    {
      if( m_p_std_ofstream->is_open() )
        m_p_std_ofstream->close();
      delete m_p_std_ofstream ;
    }
    //Set to NULL so the calling Log() evaluates the pointer address if it is
    // NULL.
    m_p_std_ofstream = NULL ;
    m_p_std_ostream = NULL;
  //  LOGN("end of ~Logger")
}

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

bool StdOfStreamLogWriter::IsOpen()
{
  bool isOpen = m_p_std_ofstream //!= NULL
    && m_p_std_ofstream->is_open() ;
  return isOpen;
}

/** ANSI version of Open */
bool StdOfStreamLogWriter::OpenA( const std::string & c_r_stdstrFilePath//,
  //bool bRolling
  )
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
//  if( bFileIsOpen )
//    if( m_p_log_formatter == NULL )
////    CreateFormatter("",
////      "%year%.%month%.%day% %hour%:%minute%:%second%s%millisecond%ms ");
//      CreateTextFormatter();
  return bFileIsOpen;
  //m_ofstream << "File Opened" ;
  //*mp_ofstream << "File Opened" ;
  //m_ofstream.close() ;
  //m_ofstream.write(arch,6) ;
  //m_ofstream.flush() ;
}

inline bool StdOfStreamLogWriter::SetStdOstream(
  const std::string & c_r_stdstrFilePath)
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
  const bool bFileIsOpen = m_p_std_ofstream->//good() ;
    //TODO "is_open" returned true
    //if no entry in file system rights was defined for user this program ran
    //under in NTFS file system running on Windows. But no file was created.
    //
    is_open() && m_p_std_ofstream->good();
  if( bFileIsOpen )
    m_p_std_ostream = m_p_std_ofstream;
  else
  {
    throw LogFileAccessException(
      //TODO Windows returns "success" even if log file could not be opened
//      ::GetErrorMessageFromLastErrorCodeA().c_str()
      LogFileAccessException::openLogFile,
      ::GetLastErrorCode(),
       c_r_stdstrFilePath.c_str()
      );
  }
  return bFileIsOpen;
}

int StdOfStreamLogWriter::RenameFileThreadUnsafe(
  const std::string & cr_std_strFilePath
  /*, enum I_LogEntryOutputter::open_mode open_mode*/)
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
      retVal =
#ifdef _WIN32
        ::GetLastError();
#else
        OperatingSystem::GetLastErrorCode();
#endif
      //"If the file is successfully renamed, a zero value is returned."
      if( retVal == 0)
      {
        m_std_strLogFilePath = cr_std_strFilePath;
        m_p_std_ofstream->open( m_std_strLogFilePath.c_str(),
          //see http://social.msdn.microsoft.com/Forums/nl-NL/vclanguage/thread/8f121287-539f-4fe1-96b6-db3e5b9306f4
          //"I do find it strange that I must add the ios_base::in flag to keep
          //iostreams from destroying the contents of the file when I also open
          //it for output with ios_base::out."
          std::ios_base::in | std::ios_base::out |
          //ate = AT End
          //see http://www.cplusplus.com/reference/iostream/ofstream/open/:
          //(at end) Set the stream's position indicator to the end of the stream on opening.
          std::ios_base::ate );
//        m_p_std_ofstream->seekp(0, std::ios_base::end);
      }
    }
//    else
//      retVal = ::LocalLanguageMessageAndErrorCodeA();
  }
  return retVal;
}

//void StdOfStreamLogWriter::TruncateFileToZeroAndRewrite()
//{
//
//}
