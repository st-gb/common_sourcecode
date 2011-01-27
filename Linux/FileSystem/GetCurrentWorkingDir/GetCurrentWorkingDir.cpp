#include "GetCurrentWorkingDir.hpp"

#include <stdlib.h> //free(...)
#include <unistd.h> //getcwd(...)

void GetCurrentWorkingDir(std::string & r_stdstr )
{
  std::string stdstr ;
  char * pchCurentWorkingDir = NULL;
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
    0) ;
  if( pchCurentWorkingDir )
  {
    r_stdstr = std::string(pchCurentWorkingDir) ;
    //Release the memory allocated inside getcwd(...)
    free( pchCurentWorkingDir ) ;
  }
}
