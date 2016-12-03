/*
 * GetCurrentDirectory.hpp
 *
 *  Created on: 03.07.2012
 *      Author: Stefan
 */

#ifndef GETCURRENTDIRECTORY_HPP_
#define GETCURRENTDIRECTORY_HPP_

#include <stdlib.h> //free(...)
#include <unistd.h> //getcwd(...)
#include <string> //class std::string

namespace Linux_
{
  inline void GetCurrentWorkingDirA_inl(std::string & r_stdstr )
  {
    std::string stdstr ;
#ifdef __ANDROID__
    char * pchCurentWorkingDir = (char *) malloc(2000);
#else
    char * pchCurentWorkingDir = NULL;
#endif
    /** http://pubs.opengroup.org/onlinepubs/009695399/functions/getcwd.html */
    //"Get the pathname of the current working directory,
    //   and put it in SIZE bytes of BUF.  Returns NULL if the
    //   directory couldn't be determined or SIZE was too small.
    //   If successful, returns BUF.
    pchCurentWorkingDir = getcwd(
      //"In GNU, if BUF is NULL,an array is allocated with `malloc' [...]"
      pchCurentWorkingDir,
      //"the array is SIZE
      //   bytes long, unless SIZE == 0, in which case it is as
      //   big as necessary."
#ifdef __ANDROID__
      2000
#else
      0
#endif
      ) ;
    if( pchCurentWorkingDir )
    {
      r_stdstr = std::string(pchCurentWorkingDir) ;
//#ifndef __ANDROID__
      //Release the memory allocated inside getcwd(...)
      free( pchCurentWorkingDir ) ;
//#endif
    }
  }
}

#endif /* GETCURRENTDIRECTORY_HPP_ */
