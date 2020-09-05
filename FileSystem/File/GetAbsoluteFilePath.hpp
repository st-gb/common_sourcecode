#ifndef GETABSOLUTEFILEPATH_HPP
#define GETABSOLUTEFILEPATH_HPP

#include <string> //class std::string
//#include <stdlib.h> //realpath(...)
#include <FileSystem/path_seperator.h>///PATH_SEPERATOR_CHAR

#ifdef _WIN32
  ///FileSystem::GetAbsolutePathA(...)
  #include <OperatingSystem/Windows/FileSystem/GetAbsolutePath.hpp>
#endif
#ifdef __linux__
  ///FileSystem::GetAbsolutePathA(...)
  #include <OperatingSystem/POSIX/FileSystem/GetAbsolutePath.hpp>
#endif
namespace FileSystem
{
inline std::string GetAbsoluteFilePath(
  const std::string & rootPath, 
  const std::string & filePath)
{
  const int lastPathSepChar = filePath.rfind(PATH_SEPERATOR_CHAR);
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
  const int lastPathSepChar = filePath.rfind(PATH_SEPERATOR_CHAR);
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
