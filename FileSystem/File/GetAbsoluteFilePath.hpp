#ifndef GETABSOLUTEFILEPATH_HPP
#define GETABSOLUTEFILEPATH_HPP

#include <string> //class std::string

namespace FileSystem
{
#ifdef _WIN32
  #define PATH_SEP_CHAR '\\'
#endif
#ifdef __linux__
  #define PATH_SEP_CHAR '/'
  #include <sys/param.h>

  inline void GetAbsolutePathA(const char * const getAbsPathFrom, std::string & absPath)
  {
    //from http://stackoverflow.com/questions/2341808/how-to-get-the-absolute-path-for-a-given-relative-path-programmatically-in-linux
    char resolved_path[PATH_MAX];
    realpath(getAbsPathFrom, resolved_path);
    absPath = resolved_path;
  }

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

inline std::wstring GetAbsoluteFilePath(
  const std::wstring & rootPath, 
  const std::wstring & filePath)
{
  const int lastPathSepChar = filePath.rfind(PATH_SEP_CHAR);
  std::wstring absoluteFilePath;
  if( lastPathSepChar != std::string::npos )
  {
    std::wstring relativeDirPath = filePath.substr(0, lastPathSepChar);
    if( relativeDirPath == L"." ) // e.g. "./executable.elf"
    {
      absoluteFilePath = rootPath + filePath.substr(lastPathSepChar, filePath.length() );
    }
    else
    {
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
  }
  return absoluteFilePath;
}

}//namespace

#endif //#ifdef GETABSOLUTEFILEPATH_HPP
