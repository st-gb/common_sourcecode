
/** GetDirContents.cpp
 *  Created on: 17.01.2018
 *      Author: s.gebauer */
#include <dirent.h> //struct dirent
#include <sys/stat.h> // stat(...)
#include <string.h> //strcat(...)
#include <vector> //class std::vector
#include <string> //class std::string

namespace FileSystem {
/** @param p_ch : NULL to get # of needed chars */
/*char * */ unsigned GetDirContents(
  const char * const dirToRetrieveContentsFrom,
  std::vector<std::string> & dirEntries
  )
{
  /** http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c */
  DIR * dir;

  struct dirent * dirEntry;
  //TODO ensure array is big enough for device file name (use MAX_PATH constant,
  // create array on heap etc.
  if( (dir = opendir(dirToRetrieveContentsFrom)) != 0 /*NULL*/)
  {
    /* print all the files and directories within directory */
    while( (dirEntry = readdir(dir) ) != /*NULL*/ 0)
    {
      dirEntries.push_back(dirEntry->d_name);
    }
    closedir (dir);
  } else {
    /* could not open directory */
//    perror ("");
//    return EXIT_FAILURE;
    return 0;
  }
// strcat(p_ch, "\n");
  return 1;
}
}