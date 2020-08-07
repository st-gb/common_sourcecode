#pragma once //include guard

//#include "IsRelativePath.hpp"
#include <FileSystem/IsRelativePath.hpp>
//#include "GetCurrentWorkingDir.hpp"
#include <OperatingSystem/Linux/FileSystem/GetCurrentWorkingDir/GetCurrentWorkingDir.hpp>
#include <string> //class std::string
#include <stdlib.h>/// realpath(...)
//#include <string.h> // strerror

namespace FileSystem
{

/** Make inline to avoid multiple definitions linker error. */
inline int GetAbsolutePathA(const char getAbsPathFrom [], std::string & absPath)
{
  std::string str;
  int e = 0;
  /** http://man7.org/linux/man-pages/man3/realpath.3.html
   " If resolved_path is specified as NULL, then realpath() uses malloc(3)
     to allocate a buffer of up to PATH_MAX" */
  char *resolved_path = NULL;
  /// Using "realpath" has the advantage of goint through symbolic links and
  ///  "..".
  ///"realpath" only seems to work for _existing_ files.
  ///https://linux.die.net/man/3/realpath : "Conforming To" "[...] POSIX"
  char * absPath = realpath(path, resolved_path);
  if( absPath == NULL )
  {
    e = errno;
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
  return e;
}

inline std::string GetAbsolutePathA(const char * const path)
{
  ///from 
  ///http://stackoverflow.com/questions/2341808/how-to-get-the-absolute-path-for-a-given-relative-path-programmatically-in-linux
  /*char resolved_path[PATH_MAX];
  realpath(getAbsPathFrom, resolved_path);
  std::string stdstrAbsPath;
  stdstrAbsPath = resolved_path;*/
  GetAbsolutePathA(path, stdstrAbsPath);
  return stdstrAbsPath;
}

};//namespace FileSystem
