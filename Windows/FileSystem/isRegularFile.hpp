#pragma once

namespace FileSystem {
inline bool IsRegularFile(const char * const fileOrDirPath)
{
  //https://stackoverflow.com/questions/146924/how-can-i-tell-if-a-given-path-is-a-directory-or-a-file-c-c
  /** https://msdn.microsoft.com/en-us/library/aa364944(VS.85).aspx */
  DWORD result = ::GetFileAttributesA(fileOrDirPath /* _In_ LPCTSTR lpFileName */ );
  if( result != INVALID_FILE_ATTRIBUTES)
    if( result & FILE_ATTRIBUTE_DIRECTORY == 0)
      return true;
  return false;
}
}
