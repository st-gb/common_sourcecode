#pragma once

#include <FileSystem/File/File.hpp>
//#ifdef _WIN32_WINNT
//  #undef _WIN32_WINNT
//#endif
//#define _WIN32_WINNT 0x0500 //for GetFileSizeEx(...)
#include <windows.h> //HANDLE

namespace Windows_API
{
  class File
    : public I_File
  {
    private:
      HANDLE m_hFile;
    public:
      File() : m_hFile(INVALID_HANDLE_VALUE) { }
      ~File();

    enum CloseError Close();
    file_pointer_type GetCurrentFilePointerPosition();
    file_pointer_type GetFileSizeInBytes();
    enum OpenError OpenA(const char * const filePath, enum I_File::OpenMode openMode);
    int ReadByte();
    bool SeekFilePointerPosition(const file_pointer_type &);
  };
}
