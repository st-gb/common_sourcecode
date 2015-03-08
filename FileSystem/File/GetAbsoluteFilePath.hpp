#ifndef GETABSOLUTEFILEPATH_HPP
#define GETABSOLUTEFILEPATH_HPP

#include <string> //class std::string

#ifdef _WIN32
  #define PATH_SEP_CHAR '\\'
#endif

inline std::string GetAbsoluteFilePath(
  const std::string & rootPath, 
  const std::string & filePath)
{
  const int lastPathSepChar = filePath.rfind(PATH_SEP_CHAR);
  std::string absoluteFilePath;
  if( lastPathSepChar != std::string::npos )
  {
    std::string relativeDirPath = filePath.substr(0, lastPathSepChar);
    const int numOverlappingDirPathChars = rootPath.rfind(relativeDirPath);
    if( numOverlappingDirPathChars != std::string::npos )
    {
      absoluteFilePath = rootPath.substr(0, rootPath.length() - 
        numOverlappingDirPathChars);
      absoluteFilePath += filePath;
    }
    else
      return filePath;
  }
  return absoluteFilePath;
}

#endif //#ifdef GETABSOLUTEFILEPATH_HPP