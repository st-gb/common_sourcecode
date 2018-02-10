/** GetDirContents.c
 *  Created on: 23.12.2015
 *      Author: s.gebauer */
#include <dirent.h> //struct dirent
#include <sys/stat.h> // stat(...)
#include <string.h> //strcat(...)

/** @param p_ch : NULL to get # of needed chars */
/*char * */ unsigned GetDirContents(
  const char * const dirToRetrieveContentsFrom,
  char * p_ch,
  unsigned * p_numFilesOrDirs
  )
{
  /** http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c */
  DIR * dir;
  unsigned ui = 0;
  * p_numFilesOrDirs = 0;

  if( p_ch != 0)
    * p_ch = '\0';
  struct dirent * dirEntry;
  //TODO ensure array is big enough for device file name (use MAX_PATH constant,
  // create array on heap etc.
  if( (dir = opendir(dirToRetrieveContentsFrom)) != 0 /*NULL*/)
  {
    /* print all the files and directories within directory */
    while( (dirEntry = readdir(dir) ) != /*NULL*/ 0)
    {
      if( p_ch != 0)
      {
        strcat(p_ch, dirEntry->d_name);
        strcat(p_ch, "\t");
        (* p_numFilesOrDirs) ++;
      }
      ui += strlen(dirEntry->d_name) + 1 /* for tabulator char */;
    }
    closedir (dir);
  } else {
    /* could not open directory */
//    perror ("");
//    return EXIT_FAILURE;
  }
// strcat(p_ch, "\n");
  return ui + 1;
}
