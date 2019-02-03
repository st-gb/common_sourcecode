#pragma once///Include guard
#include <sys/stat.h>///int lstat(...), struct stat
#ifdef _DEBUG
  #include <errno.h>///errno
#endif
//from http://stackoverflow.com/questions/3536781/accessing-directories-in-c

namespace FileSystem {
inline bool IsRegularFile(const char * const fileOrDirPath)
{
  struct stat fileStatus;
  /** lstat is POSIX compatible, see https://linux.die.net/man/2/lstat */
  const int retVal = lstat(fileOrDirPath, &fileStatus);
  ///https://linux.die.net/man/2/lstat : "On success, zero is returned. On error
  /// , -1 is returned, and errno is set appropriately."
  if( retVal )
  {
#ifdef _DEBUG
    int i = errno;///Just for debugging
#endif
    return false;
  }
  /** Regular file, i.e. not a block device file etc. */
  if(S_ISREG(fileStatus.st_mode) )
    return true;
  //else
  return false;
}
}
