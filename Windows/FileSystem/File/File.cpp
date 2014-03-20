#include "File.hpp"

//#include <windows.h> // ::CreateFileA(...)
//#include <FileAPI.h>

namespace Windows_API
{
//  class File
//  {

    File::~File()
    {
      ::CloseHandle( m_hFile);
    }

    enum I_File::CloseError File::Close()
    {
      if( m_hFile != INVALID_HANDLE_VALUE )
      {
        BOOL retVal = ::CloseHandle(m_hFile);
        if( retVal )
        {
          m_hFile = INVALID_HANDLE_VALUE;
          return I_File::closingFileSucceeded;
        }
//        return I_File::closingFileFailed;
      }
//      else
//        return I_File::alreadyClosed;
      return I_File::closingFileFailed;
    }

    I_File::file_pointer_type File::GetCurrentFilePointerPosition()
    {
      //http://stackoverflow.com/questions/17707020/is-there-no-getfilepointerex-windows-api-function
      LARGE_INTEGER liOfs={0};
      LARGE_INTEGER liNew={0};
      ::SetFilePointerEx(m_hFile, liOfs, &liNew, FILE_CURRENT);
      return liNew.QuadPart;
    }

    I_File::file_pointer_type File::GetFileSizeInBytes()
    {
//      LARGE_INTEGER li;
      I_File::file_pointer_type fileSize;
      DWORD fileSizeHigh;
      //http://msdn.microsoft.com/en-us/library/windows/desktop/aa364957%28v=vs.85%29.aspx
      //BOOL b = GetFileSizeEx(
      //http://msdn.microsoft.com/en-us/library/windows/desktop/aa364955%28v=vs.85%29.aspx
      DWORD dwfileSizeLow = ::GetFileSize(
        m_hFile ,// _In_   HANDLE hFile,
//        & li //_Out_  PLARGE_INTEGER lpFileSize
        & fileSizeHigh
      );
//      return /*li.QuadPart;*/
      if( dwfileSizeLow == INVALID_FILE_SIZE )
        if( ::GetLastError() != NO_ERROR )
          return -1;
      fileSize = fileSizeHigh;
      fileSize <<= sizeof(DWORD) * 8; //32;
      fileSize |= dwfileSizeLow;
      return fileSize;
    }

    enum I_File::OpenError File::OpenA(const char * const filePath,
        enum I_File::OpenMode openMode)
    {
      enum I_File::OpenError openError = I_File::not_set;
      DWORD dwDesiredAccess = 0, dwCreationDisposition = 0;
      switch(openMode)
      {
      case readOnly:
        dwDesiredAccess = GENERIC_READ;
        dwCreationDisposition = OPEN_EXISTING;
        break;
      case writeOnly:
        //    Creates a new file, always.
        //    If the specified file exists and is writable, the function overwrites the
        //      file, the function succeeds, and last-error code is set to
        //      ERROR_ALREADY_EXISTS (183).
        //    If the specified file does not exist and is a valid path, a new file is
        //      created, the function succeeds, and the last-error code is set to zero.
        dwCreationDisposition = CREATE_ALWAYS;
        break;
      }
      m_hFile = ::CreateFileA(
        filePath, //__in      LPCTSTR lpFileName,
        dwDesiredAccess, //__in      DWORD dwDesiredAccess,
        //__in      DWORD dwShareMode,
          FILE_SHARE_READ,
  //        0, // do not share
        NULL, //__in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        dwCreationDisposition, //__in      DWORD dwCreationDisposition,
        //__in      DWORD dwFlagsAndAttributes,
//        dwFlagsAndAttributes
        FILE_ATTRIBUTE_NORMAL
        , NULL //__in_opt  HANDLE hTemplateFile
        );
      const DWORD dwLastError = ::GetLastError();
      switch(dwLastError)
      {
      case ERROR_SUCCESS:
        openError = I_File::success;
        break;
      case ERROR_FILE_NOT_FOUND:
        openError = I_File::fileNotFound;
        break;
      case ERROR_ACCESS_DENIED:
        openError = I_File::accessDenied;
        break;
      }
      return openError;
    }

    int File::ReadByte()
    {
      BYTE by;
      DWORD dwNumberOfBytesRead;
      //"If the function succeeds, the return value is nonzero (TRUE)."
      BOOL b = ::ReadFile(
          m_hFile, //HANDLE hFile,
          & by, //_Out_        LPVOID lpBuffer,
          1, //_In_         DWORD nNumberOfBytesToRead,
          & dwNumberOfBytesRead, //_Out_opt_    LPDWORD lpNumberOfBytesRead,
          NULL //_Inout_opt_  LPOVERLAPPED lpOverlapped
          );
      if( ! b || dwNumberOfBytesRead < 1 )
        return -1;
      return by;
    }

    bool File::SeekFilePointerPosition(const I_File::file_pointer_type & offset)
    {
      LARGE_INTEGER liOfs={offset};
      LARGE_INTEGER liNew={0};
      //http://msdn.microsoft.com/en-us/library/windows/desktop/aa364957%28v=vs.85%29.aspx
      //"If the function succeeds, the return value is nonzero."
      return ::SetFilePointerEx(m_hFile, liOfs, &liNew, FILE_BEGIN);
    }
//  };
}
