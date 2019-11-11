#pragma once
#include <Windows.h> //GetFileAttributesA(...)

namespace FileSystem {
inline bool IsDirectory(const char * const fileOrDirPath)
{
  //https://stackoverflow.com/questions/146924/how-can-i-tell-if-a-given-path-is-a-directory-or-a-file-c-c
  /** https://msdn.microsoft.com/en-us/library/aa364944(VS.85).aspx */
  DWORD result = GetFileAttributesA(fileOrDirPath /* _In_ LPCTSTR lpFileName */ );
  if( result & FILE_ATTRIBUTE_DIRECTORY)
    return true;
  return false;
}
}