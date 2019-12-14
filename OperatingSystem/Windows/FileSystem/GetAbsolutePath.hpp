#pragma once

#include<string>///class std::string

namespace FileSystem {
inline std::string GetAbsolutePathA(const char path []) {
  ///https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfullpathnamea
  DWORD retVal = ::GetFullPathNameA(path, 0, NULL, NULL);
  if(retVal > 0)
  {
    const DWORD numChars = retVal +1;
    char absPath[numChars];
    retVal = GetFullPathNameA(path, numChars, absPath, NULL);
	return std::string(absPath);
  }
  return "";
}
}