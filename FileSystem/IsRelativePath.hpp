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
  inline bool IsRelativePathA(const char * const path)
  {
    //from http://stackoverflow.com/questions/853177/win32-api-for-determining-if-a-path-is-relative-or-absolute
    /* http://msdn.microsoft.com/en-us/library/bb773660%28VS.85%29.aspx
    * "Returns TRUE if the path is relative, or FALSE if it is absolute." */
    BOOL b = ::PathIsRelativeA(path);
    return b;
  }
}
#endif //#ifdef _WIN32

#endif /* ISRELATIVEPATH_HPP_ */
