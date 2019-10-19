#pragma once //include guard

//#include "IsRelativePath.hpp"
#include <FileSystem/IsRelativePath.hpp>
//#include "GetCurrentWorkingDir.hpp"
#include <OperatingSystem/Linux/FileSystem/GetCurrentWorkingDir/GetCurrentWorkingDir.hpp>
#include <string> //class std::string
#include <stdlib.h> // realpath(...))
//#include <string.h> // strerror

namespace FileSystem
{

/** Make inline to avoid multiple definitions linker error. */
inline std::string GetAbsolutePathA(const char * const path)
{
  std::string str;
  /** http://man7.org/linux/man-pages/man3/realpath.3.html
   " If resolved_path is specified as NULL, then realpath() uses malloc(3)
     to allocate a buffer of up to PATH_MAX" */
  char *resolved_path = NULL;
  /// Using "realpath" has the advantage of goint through symbolic links and
  ///  "..".
  ///"realpath" only seems to work for _existing_ files.
  char * absPath = realpath(path, resolved_path);
  if( absPath == NULL )
  {
    int e = errno;
    //char * errStr = strerror(e);
    //e = e + 1;
    if( FileSystem::IsRelativePathA( path) )
    {
      std::string currentWorkingDir;
      //TODO also handle ".." in file path!
      OperatingSystem::GetCurrentWorkingDirA_inl(currentWorkingDir);
      str = currentWorkingDir + "/" + path;
    }
    else /** Already an absolute path. */
      str = path;
  }
  else
  {
    str = absPath;
//  /** http://man7.org/linux/man-pages/man3/realpath.3.html :
//   *  "The caller should deallocate this buffer using free(3)." */
    free(absPath);
  }  
  return str;
}

};//namespace FileSystem
