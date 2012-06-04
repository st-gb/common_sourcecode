#include <Controller/FileSystem/SetCurrentWorkingDir.hpp>

#include <stdlib.h> //free(...)
#include <unistd.h> //getcwd(...)

//extern "C"
//{
  inline int SetCurrentWorkingDir(//std::string & r_stdstr
    const char * pchCurrentWorkingDir)
  {
  //  char * pchCurrentWorkingDir = NULL;
    //http://linux.die.net/man/2/chdir:
    //"On success, zero is returned. On error, -1 is returned, and errno is set
    //appropriately."
    int nReturnValue = chdir(
      //"In GNU, if BUF is NULL,an array is allocated with `malloc' [...]"
      pchCurrentWorkingDir) ;
    return nReturnValue;
  }

  int SetCurrentDirectory(//std::string & r_stdstr
    const char * pchCurrentWorkingDir)
  {
    return SetCurrentWorkingDir(pchCurrentWorkingDir);
  }
//}
