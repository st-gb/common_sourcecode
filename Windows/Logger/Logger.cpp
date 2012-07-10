/*
 * Logger.cpp
 *
 *  Created on: 05.07.2012
 *      Author: Stefan
 */

#include "Logger.hpp"

namespace Windows_API
{

  Logger::Logger()
    : m_hFile(INVALID_HANDLE_VALUE)
  {
//    CreateFormatter();
    if( m_p_log_formatter )
      m_p_log_formatter->SetStdOstream( & GetStdOstream() );
  }

  Logger::~Logger()
  {
    ::CloseHandle(m_hFile);
  }
//  OpenFile2

  bool Logger::OpenFile2( const std::string & c_r_stdstrFilePath )
  {
    return OpenFlushingFile(c_r_stdstrFilePath);
  }

#ifdef _WIN32
  //http://msdn.microsoft.com/en-us/library/windows/desktop/aa364439%28v=vs.85%29.aspx:
  //"To open a file for unbuffered I/O, call the CreateFile function with the
  //FILE_FLAG_NO_BUFFERING and FILE_FLAG_WRITE_THROUGH flags. This prevents the
  //file contents from being cached and flushes the metadata to disk with each
  //write.
  bool Logger::OpenFlushingFile(const std::string & c_r_stdstrFilePath)
  {
//    if( ! m_p_std_ofstream )
//      m_p_std_ofstream = new std::ostringstream ;
    m_hFile = ::CreateFileA(
      c_r_stdstrFilePath.c_str(), //__in      LPCTSTR lpFileName,
      //__in      DWORD dwDesiredAccess,
        GENERIC_WRITE,
      //__in      DWORD dwShareMode,
        FILE_SHARE_READ,
//        0, // do not share
      NULL, //__in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  //    Creates a new file, always.
  //    If the specified file exists and is writable, the function overwrites the
  //      file, the function succeeds, and last-error code is set to
  //      ERROR_ALREADY_EXISTS (183).
  //    If the specified file does not exist and is a valid path, a new file is
  //      created, the function succeeds, and the last-error code is set to zero.
      CREATE_ALWAYS, //__in      DWORD dwCreationDisposition,
      //__in      DWORD dwFlagsAndAttributes,
      FILE_ATTRIBUTE_NORMAL //|
      //"If FILE_FLAG_WRITE_THROUGH and FILE_FLAG_NO_BUFFERING are both
      //specified, so that system caching is not in effect, then the data is
      //immediately flushed to disk without going through the Windows system
      //cache. The operating system also requests a write-through of the hard
      //disk's local hardware cache to persistent media."

      //FILE_FLAG_WRITE_THROUGH |
//      FILE_FLAG_NO_BUFFERING
      ,NULL //__in_opt  HANDLE hTemplateFile
      );
#ifdef _DEBUG
    DWORD dwLastError = ::GetLastError();
    if( dwLastError == ERROR_ALREADY_EXISTS )
      dwLastError = ERROR_ALREADY_EXISTS;
#endif //#ifdef _DEBUG
    if( m_hFile == INVALID_HANDLE_VALUE)
      return false;
    return true;
  }
#endif

//  int Logger::RenameFile(const std::string & cr_std_strFilePath)
//  {
//
//  }
  DWORD Logger::WriteToFile()
  {
    if( m_hFile != INVALID_HANDLE_VALUE )
    {
      DWORD dwNumberOfBytesWritten;
      const std::string & r_std_str = m_std_stringstream.str();
      DWORD dwSize = r_std_str.length();
      const char * p_ch = r_std_str.c_str();
      //error code may have been set to "ERROR_ALREADY_EXISTS" from CreateFile(...)
      ::SetLastError(ERROR_SUCCESS);
      BOOL b =
  //#ifdef _WIN32
      ::WriteFile(
        m_hFile, //__in         HANDLE hFile,
        p_ch, //__in         LPCVOID lpBuffer,
        dwSize, //__in         DWORD nNumberOfBytesToWrite,
        & dwNumberOfBytesWritten, //__out_opt    LPDWORD lpNumberOfBytesWritten,
        NULL //__inout_opt  LPOVERLAPPED lpOverlapped
        );
      FlushFileBuffers(m_hFile);
      if( b )
        m_std_stringstream.str(""); //clear: set the internal string to empty string.
      else
      {
      }
      DWORD dw = ::GetLastError();
      //"FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING" in CreateFile(...)
      // leads to error code "87" after WriteFile(...)
      return dw;
    }
    return 1;
//    ++ dw;
    //"If the function succeeds, the return value is nonzero (TRUE)."
//#else
//    m_p_std_ofstream->flush() ;
//#endif
    //see http://www.velocityreviews.com/forums/t278533-std-stringstream-reset.html
  }
  void TruncateFileSizeToZero()
  {
    //TODO implement
  }
} /* namespace Windows_API */
