#include "File.hpp"

//#include <windows.h> // ::CreateFileA(...)
//#include <FileAPI.h>
#include <FileSystem/File/FileReadException.hpp>
#include <FileSystem/File/EndOfFileException.hpp>
#include <FileSystem/File/GetAbsoluteFilePath.hpp>
#include <FileSystem/GetCurrentWorkingDir.hpp>

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
      const BOOL success = ::SetFilePointerEx(m_hFile, liOfs, &liNew, FILE_CURRENT);
      if( ! success )
      {
//        liNew.HighPart = MAXDWORD;
//        liNew.LowPart = MAXDWORD;
        liNew.QuadPart = -1;
      }
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
      m_filePathA = filePath;
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
        {
        std::string std_strCurrentWorkingDir;
        OperatingSystem::GetCurrentWorkingDirA_inl(std_strCurrentWorkingDir);
        m_filePathA = FileSystem::GetAbsoluteFilePath(std_strCurrentWorkingDir, filePath);
        }
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

    /** @return a single byte f*/
    int File::ReadByte()
    {
      BYTE fileByte;
      int returnValue = -1;
      DWORD dwNumberOfBytesRead;
      const DWORD nNumberOfBytesToRead = 1;
      //"If the function succeeds, the return value is nonzero (TRUE)."
      const BOOL readFileReturnValue = ::ReadFile(
          m_hFile, //HANDLE hFile,
          & fileByte, //_Out_        LPVOID lpBuffer,
          nNumberOfBytesToRead, //_In_         DWORD nNumberOfBytesToRead,
          & dwNumberOfBytesRead, //_Out_opt_    LPDWORD lpNumberOfBytesRead,
          NULL //_Inout_opt_  LPOVERLAPPED lpOverlapped
          );
      if( readFileReturnValue )
      {
        /** https://msdn.microsoft.com/en-us/library/windows/desktop/aa365467%28v=vs.85%29.aspx :
         *  "When a synchronous read operation reaches the end of a file, 
         *  ReadFile returns TRUE and sets *lpNumberOfBytesRead to zero." */
        if( dwNumberOfBytesRead == 0 )
        {
#ifdef _DEBUG
          const DWORD dw = ::GetLastError();
#endif
          //return I_File::endOfFileReached;
          EndOfFileException endOfFileException(m_filePathA.c_str () );
          throw endOfFileException;
        }
        else if( dwNumberOfBytesRead < nNumberOfBytesToRead )
        {
          const DWORD osErrorCode = GetLastError();
          if( osErrorCode == ERROR_SUCCESS )
          {
            //return I_File::readLessThanIntended;
            EndOfFileException endOfFileException(m_filePathA.c_str () );
            throw endOfFileException;
          }
          else
          {
            FileReadException fileReadException(
              I_File::unknownReadError, 
              osErrorCode, m_filePathA.c_str () );
            throw fileReadException;
          }
        }
      }
      /** http://msdn.microsoft.com/en-us/library/windows/desktop/aa365467%28v=vs.85%29.aspx:
       *  "If the function fails, or is completing asynchronously, the return 
       *  value is zero (FALSE). To get extended error information, call the 
       *  GetLastError function." */
      else
      {
        const DWORD osErrorCode = GetLastError();
//        if( dwNumberOfBytesRead < 1 )
//        else
        //return I_File::unknownReadError;
        FileReadException fileReadException(
          I_File::unknownReadError, 
          osErrorCode, m_filePathA.c_str () );
        throw fileReadException;
      }
      return /*I_File::successfullyRead*/ fileByte;
    }

    enum I_File::SeekResult File::SeekFilePointerPosition(const I_File::file_pointer_type & offset)
    {
      LARGE_INTEGER liOfs={offset};
      LARGE_INTEGER liNew={0};
      /** http://msdn.microsoft.com/en-us/library/windows/desktop/aa364957%28v=vs.85%29.aspx
      * "If the function succeeds, the return value is nonzero." */
      const BOOL setFilePointerExSucceeded = ::SetFilePointerEx(m_hFile, liOfs,
        & liNew, FILE_BEGIN);
      return setFilePointerExSucceeded ? successfullySeeked : notAseekableStream;
    }
//  };
}
