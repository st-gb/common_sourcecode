/*
 * GetBlockDeviceFiles.c
 *
 *  Created on: 17.10.2015
 *      Author: s.gebauer
 */

#include <dirent.h> //struct dirent
#include <sys/stat.h> // stat(...)
#include <string.h> //strcat(...)
#include <stdio.h> //sprintf(...)
#include <stdlib.h> //malloc(...)
//#include <sys/types.h>

#define DEVICE_FILE_PATH_LEN 261///256+ /dev/

/** for getting just block device files without /dev/ram an so on:
 * cat /proc/partitions
* https://wiki.ubuntuusers.de/Datentr%C3%A4ger
* sudo blkid -o list -w /dev/null:
* "/dev/sdg5   ext3   ext3  /media/ext3  3a1be9f2-b1d3-41b6-b144-75853b6d2c5a"
* libblkid */
//TODO the "double calling" approach can fail if between two calls an additional
//   block device comes up
//TODO show additional information like partition start, end, size from
// file like "/sys/block/sdg/sdg1/start"
/*char * */ unsigned GetBlockDeviceFiles(char * p_ch)
{
  /** http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c */
//  uint64_t size;
  DIR * dir;
  unsigned ui = 0;

  struct dirent * dirEntry;
//  char files[100] = "";
  //TODO ensure array is big enough for device file name (use MAX_PATH constant,
  // create array on heap etc.
  char filePath[DEVICE_FILE_PATH_LEN /*MAX_PATH*/] = "/dev/";
  if( (dir = opendir ("/dev/")) != 0 /*NULL*/)
  {
    /* print all the files and directories within directory */
    while( (dirEntry = readdir (dir)) != /*NULL*/ 0)
    {
      /** Prevent stack overflow with this condition. */
      if( strlen(dirEntry->d_name) < DEVICE_FILE_PATH_LEN - 
        /** "/dev/" = 5 chars + string terminating char = 6 chars */ 6 )
      {
//      char * fileName = malloc( strlen(dirEntry->d_name) + 1);
        snprintf(filePath, DEVICE_FILE_PATH_LEN, "/dev/%s", dirEntry->d_name);
  //      strcpy(filePath + 4, ent->d_name);
        struct stat statObj;
  //      strcpy()
        int i = stat (filePath /*const char *filename*/, & statObj);
        if( i == 0)
        {
          /** http://linux.die.net/man/2/stat */
          int isBlockDevice = S_ISBLK(statObj.st_mode); /// & S_IFMT == ;
          if( isBlockDevice)
          {
  //          uint64_t size = GetDeviceSize(/*ent->d_name*/ filePath);
  //          printf ("%s: %llu\n", dirEntry->d_name, size);
    //      strcat(files, "\n");
    //      strcat(files, ent->d_name);
            if( p_ch != 0)
            {
              strcat(p_ch, dirEntry->d_name);
              strcat(p_ch, "\t");
            }
            ui += strlen(dirEntry->d_name) + 1 /** tabulator character */ ;
          }
        }
      }
    }
    closedir (dir);
  } else {
    /* could not open directory */
//    perror ("");
//    return EXIT_FAILURE;
  }
// strcat(p_ch, "\n");
  return ui + 1 /** string terminating */ ;
}
