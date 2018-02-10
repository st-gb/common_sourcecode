
#include <sys/stat.h> //lstat
//from http://stackoverflow.com/questions/3536781/accessing-directories-in-c

namespace FileSystem {
inline bool IsRegularFile(const char * const fileOrDirPath)
{
  struct stat st;
  /** lstat is POSIX compatible, see https://linux.die.net/man/2/lstat */
  lstat(fileOrDirPath, &st);
  /** Regular file, i.e. not a block device file etc. */
  if(S_ISREG(st.st_mode) )
    return true;
  //else
  return false;
}
}
