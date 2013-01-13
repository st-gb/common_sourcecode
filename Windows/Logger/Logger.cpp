/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
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
    : m_hFile(INVALID_HANDLE_VALUE),
      m_buffer(NULL),
      m_dwBufferSize(0),
      m_dwGetLastErrorAfterCreateFileA(MAXDWORD)
  {
//    CreateFormatter();
//    if( m_p_log_formatter )
//      m_p_log_formatter->SetStdOstream( & GetStdOstream() );
  }

  /** Calls base class' "::Logger::~Logger()" and then the other code*/
  Logger::~Logger()
  {
    ::CloseHandle(m_hFile);
    if( m_buffer)
      ::VirtualFree(
        m_buffer,       // Base address of block
        0,             // Bytes of committed pages
        MEM_RELEASE);  // Decommit the pages
  }
//  OpenFile2

//  bool Logger::OpenFile2( const std::string & c_r_stdstrFilePath )
//  {
//    return OpenFlushingFile(c_r_stdstrFilePath);
//  }
  bool Logger::SetStdOstream(const std::string & c_r_stdstrFilePath)
  {
    bool fileIsOpen = OpenFlushingFile(c_r_stdstrFilePath);
    m_p_std_ostream = & GetStdOstream();
    if( m_p_log_formatter )
      //When m_p_std_ofstream is <> NULL then it is logged to output.
      m_p_log_formatter->SetStdOstream( m_p_std_ostream );
    return fileIsOpen;
  }

#ifdef _WIN32
  //"If FILE_FLAG_WRITE_THROUGH and FILE_FLAG_NO_BUFFERING are both
  //specified, so that system caching is not in effect, then the data is
  //immediately flushed to disk without going through the Windows system
  //cache. The operating system also requests a write-through of the hard
  //disk's local hardware cache to persistent media."
#define WRITE_THROUGH_AND_NO_BUFFERING FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING

  //http://msdn.microsoft.com/en-us/library/windows/desktop/aa364439%28v=vs.85%29.aspx:
  //"To open a file for unbuffered I/O, call the CreateFile function with the
  //FILE_FLAG_NO_BUFFERING and FILE_FLAG_WRITE_THROUGH flags. This prevents the
  //file contents from being cached and flushes the metadata to disk with each
  //write.
  bool Logger::OpenFlushingFile(const std::string & c_r_stdstrFilePath)
  {
//    if( ! m_p_std_ofstream )
//      m_p_std_ofstream = new std::ostringstream ;
    DWORD dwFlagsAndAttributes =
      /** Tested: open with "FILE_ATTRIBUTE_NORMAL" and call FlushFileBuffers()
      // after WriteFile() causes the content to be written immediately, but takes
       * 100 ms . */
//      FILE_ATTRIBUTE_NORMAL //|
//      WRITE_THROUGH_AND_NO_BUFFERING
      FILE_FLAG_WRITE_THROUGH //content is more up-to-date than without
//      FILE_FLAG_NO_BUFFERING
      ;
    //Must delete the file first because: if the file already exists but is
    // not writable (due to security rights) CreateFileA() just returns
    // ERROR_ALREADY_EXISTS with "CREATE_ALWAYS" but not the "access denied"
    // error code.
    BOOL b = ::DeleteFileA(
      c_r_stdstrFilePath.c_str() //_In_  LPCTSTR lpFileName
      );
    DWORD dwLastError = ::GetLastError();
    //http://msdn.microsoft.com/en-us/library/windows/desktop/aa363915%28v=vs.85%29.aspx:
    //"If an application attempts to delete a file that does not exist, the
    //DeleteFile function fails with ERROR_FILE_NOT_FOUND
    if( b || ( !b && ( dwLastError == ERROR_FILE_NOT_FOUND ||
        dwLastError == ERROR_PATH_NOT_FOUND) )
      )
    {
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
        dwFlagsAndAttributes
        ,NULL //__in_opt  HANDLE hTemplateFile
        );
      m_dwGetLastErrorAfterCreateFileA = ::GetLastError();
  //    LOGN_DEBUG("GetLastError after CreateFileA:" << dwLastError)
      if( dwFlagsAndAttributes & //WRITE_THROUGH_AND_NO_BUFFERING
          FILE_FLAG_NO_BUFFERING )
      {
        SYSTEM_INFO sSysInfo;         // Useful information about the system
        ::GetSystemInfo(&sSysInfo);     // Initialize the structure.
        m_dwBufferSize = sSysInfo.dwPageSize;
        //see http://msdn.microsoft.com/en-us/library/windows/desktop/cc644950%28v=vs.85%29.asp
        //use "VirtualAlloc"
        m_buffer = ::VirtualAlloc( NULL, //0 //dwSize
          m_dwBufferSize
          , MEM_COMMIT, PAGE_READWRITE);
        if( m_hFile == INVALID_HANDLE_VALUE || m_buffer == NULL )
          return false;
      }
  #ifdef _DEBUG
      DWORD dwLastError = ::GetLastError();
      if( dwLastError == ERROR_ALREADY_EXISTS )
        dwLastError = ERROR_ALREADY_EXISTS;
  #endif //#ifdef _DEBUG
      if( m_hFile == INVALID_HANDLE_VALUE
//          || m_dwGetLastErrorAfterCreateFileA != ERROR_SUCCESS
          )
        return false;
      return true;
    }
    else
      return false;
  }
#endif

//  int Logger::RenameFile(const std::string & cr_std_strFilePath)
//  {
//
//  }
  int Logger::RenameFileThreadUnsafe(const std::string & r_std_strNewFilePath)
  {
    int retVal = 1;
    if( //http://msdn.microsoft.com/en-us/library/windows/desktop/ms724211%28v=vs.85%29.aspx:
        //"If the function succeeds, the return value is nonzero."
        ::CloseHandle(m_hFile) )
    {
      //Delete a possible file with that name, else can not be renamed to it.
      ::DeleteFileA(r_std_strNewFilePath.c_str() );
      if( //http://msdn.microsoft.com/en-us/library/windows/desktop/aa365239%28v=vs.85%29.aspx:
          //"If the function succeeds, the return value is nonzero."
        ::MoveFileA(m_std_strLogFilePath.c_str(), r_std_strNewFilePath.c_str() )
        )
      {
        if( //OpenFlushingFile(r_std_strNewFilePath)
            OpenFileA(r_std_strNewFilePath) )
          retVal = 0;
      }
      else
      {
        retVal = ::GetLastError();
      }
    }
    else
      retVal = ::GetLastError();
    return retVal;
  }

  DWORD Logger::WriteToFile()
  {
    if( m_hFile != INVALID_HANDLE_VALUE )
    {
      DWORD dwNumberOfBytesWritten;
//      if( )
      const std::string & r_std_str = m_std_stringstream.str();
      DWORD dwSizeOfCharStringToWriteInByte = r_std_str.length();
      const char * p_ch = r_std_str.c_str();
//      memcpy(m_buffer, p_ch, dwSizeOfCharStringToWriteInByte);
      //error code may have been set to "ERROR_ALREADY_EXISTS" from CreateFile(...)
      ::SetLastError(ERROR_SUCCESS);
      /** if opened with FILE_FLAG_NO_BUFFERING:
       * http://msdn.microsoft.com/en-us/library/windows/desktop/cc644950%28v=vs.85%29.aspx
       *
       */
      BOOL b =
  //#ifdef _WIN32
      ::WriteFile(
        m_hFile, //__in         HANDLE hFile,
        p_ch, //__in         LPCVOID lpBuffer,
        //m_buffer,
        dwSizeOfCharStringToWriteInByte, //__in         DWORD nNumberOfBytesToWrite,
        & dwNumberOfBytesWritten, //__out_opt    LPDWORD lpNumberOfBytesWritten,
        NULL //__inout_opt  LPOVERLAPPED lpOverlapped
        );
//      FlushFileBuffers(m_hFile);
      if( b )
        m_std_stringstream.str(""); //clear: set the internal string to empty string.
      else
      {
      }
      DWORD dw = ::GetLastError();
      //"FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING" in CreateFile(...)
      // leads to error code "87" (ERROR_INVALID_PARAMETER) after WriteFile(...)
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
