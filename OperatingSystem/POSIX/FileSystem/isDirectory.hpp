
#include <sys/stat.h> //lstat
//from http://stackoverflow.com/questions/3536781/accessing-directories-in-c

namespace FileSystem {
inline bool IsDirectory(const char * const fileOrDirPath)
{
  struct stat st;
  /** lstat is POSIX compatible, see https://linux.die.net/man/2/lstat */
  lstat(fileOrDirPath, &st);
  if(S_ISDIR(st.st_mode) )
    return true;
  //else
  return false;
}
}
