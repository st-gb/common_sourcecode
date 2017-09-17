#pragma once

//#include <io.h> //access(...)
//namespace POSIX
//{
/** Use "inline" to avoid multiple definitions.error **/
inline bool FileExists(const char *pathname)
{
  /** https://linux.die.net/man/2/access : 
    * "F_OK tests for the existence of the file" */
  return access(pathname, F_OK /*int mode*/ ) == 0;
}
//}

