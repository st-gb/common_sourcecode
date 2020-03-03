/*
 * IsRelativePath.hpp
 *
 *  Created on: 19.02.2014
 *      Author: mr.sys
 */

#ifndef ISRELATIVEPATH_HPP_
#define ISRELATIVEPATH_HPP_

#ifdef _WIN32
#include <shlwapi.h> //BOOL PathIsRelative(..)

namespace FileSystem
{
  /** Must be declared "inline", else multiple definitions of this function
   *  are possible -> error when linking. */
  inline bool IsRelativePathA(const char * const path){
    //from http://stackoverflow.com/questions/853177/win32-api-for-determining-if-a-path-is-relative-or-absolute
    /* http://msdn.microsoft.com/en-us/library/bb773660%28VS.85%29.aspx
    * "Returns TRUE if the path is relative, or FALSE if it is absolute." */
    BOOL b = ::PathIsRelativeA(path);
    return b;
  }
  inline bool IsRelativePathW(const wchar_t path []){
    BOOL b = ::PathIsRelativeW(path);
    return b;
  }
}
#endif //#ifdef _WIN32

#ifdef __linux__
//TODO move to OperatingSystem/Unix/FileSystem/IsRelPath.hpp?
// because paths in Unix start at "/" :
//  https://de.wikipedia.org/wiki/Unix#Aufbau_und_Merkmale
#include <stddef.h> //NULL

namespace FileSystem
{
  /** Must be declared "inline", else multiple definitions of this function
   *  may exist -> error when linking. */
  inline bool IsRelativePathA(const char path [])
  {
    ///Only return true if path is <> NULL and does not start with "/"
    if( path != NULL && path[0] != '/' )
      return true;
    return false;
  }
  
  inline bool IsRelativePathW(const wchar_t path [])
  {
    if( path != NULL && path[0] != L'/' )
      return true;
    return false;
  }
  inline bool IsRelativePathW(const wchar_t path [])
  {
    if( path != NULL && path[0] == L'/' )
      return false;
    return true;
  }
}
#endif

#endif /* ISRELATIVEPATH_HPP_ */
