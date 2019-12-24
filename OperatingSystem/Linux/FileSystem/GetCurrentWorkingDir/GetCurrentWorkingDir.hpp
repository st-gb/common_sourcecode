/** GetCurrentDirectory.hpp
 *  Created on: 03.07.2012
 *  Author: Stefan */

#ifndef GETCURRENTDIRECTORY_HPP_
#define GETCURRENTDIRECTORY_HPP_

#include <stdlib.h> //free(...)
#include <unistd.h> //getcwd(...)
#include <string> //class std::string

namespace /*Linux_*/ OperatingSystem
{
inline void GetCurrentWorkingDirA_inl(std::string & r_stdstr )
{
    std::string stdstr ;
//#ifdef __ANDROID__
  //TODO Setting the size self is imperfect because it may be too large or
  // insufficient.
  // But on the other hand on Android (or Linux?) allocating by "getcwd"
  // did not work.
  const size_t numBytes = 2000;
    char * pchCurentWorkingDir = (char *) malloc(numBytes);
//#else
//    char * pchCurentWorkingDir = NULL;
//  const size_t numBytes = 0;
//#endif
//  int errCode = errno;
  /** Set to 0 to ensure an error code came from the call to "getcwd" and not
   * from a previous function/system call. */
  errno = 0;
  /** http://pubs.opengroup.org/onlinepubs/009695399/functions/getcwd.html */
  /** "Get the pathname of the current working directory,
   *   and put it in SIZE bytes of BUF.  Returns NULL if the
   *   directory couldn't be determined or SIZE was too small.
   *   If successful, returns BUF. */
    pchCurentWorkingDir = getcwd(
      //"In GNU, if BUF is NULL,an array is allocated with `malloc' [...]"
      pchCurentWorkingDir,
      //"the array is SIZE
      //   bytes long, unless SIZE == 0, in which case it is as
      //   big as necessary."
      numBytes
      );
//  errCode = errno;
  /** Error code was 13 (EACCES="Permission denied") and path was "/".
   * This may be due to insufficient rights in the current working dir. */
    if( errno == 0 && pchCurentWorkingDir )
    {
      r_stdstr = std::string(pchCurentWorkingDir) ;
    }
//#ifndef __ANDROID__
      ///Release the memory allocated inside getcwd(...)
      free( pchCurentWorkingDir ) ;
//#endif
  }
}

#endif /* GETCURRENTDIRECTORY_HPP_ */
