/*
 * GetSectorSize.c
 *
 *  Created on: 01.01.2016
 *      Author: ubuntu
 */

#include <stdint.h> //uint64_t
#include <sys/ioctl.h> //ioctl(...)
#include <fcntl.h> //O_RDONLY, open(...)
#include <linux/fs.h> //BLKSSZGET
#include <unistd.h> //close(...)

/** https://en.wikipedia.org/wiki/Ioctl 
 *   "The ioctl system call first appeared in Version 7 of Unix under that name." 
    uses ioctl(...), so put it in a folder/namespace called "Unix"  */
#ifdef __cplusplus__
//namespace Unix {
#endif

/** @return 0 if an error occured, 
 *          else log. sector size of a HDD etc. in bytes. */
uint64_t GetLogicalSectorSizeInBytes(const char * const filePath)
{
  /** From http://www.linuxproblem.org/art_20.html */
  int fileDescriptor;

  fileDescriptor = open(filePath, O_RDONLY);
  if( fileDescriptor < 0 )
    return 0;
  unsigned long sectorSizeInBytes = 0;
  /** http://www.linuxproblem.org/art_20.html */
  int retVal = ioctl(fileDescriptor,
    /** http://www.cgsecurity.org/wiki/Menu_Geometry */
    /** ioctl(...) with BLKSSZGET as parameter returns the LOGICAL sector size 
     *  in bytes because for a HDD, model "HGST HTS725050A7E630", 
     *  firmware "GH2OA560", Serial Number:TF755AWHKU3RVM 
     *  "hdparm -I /dev/sda" output: 
     *   Logical  Sector size:                   512 bytes
     *   Physical Sector size:                  4096 bytes
     *  
     *  ioctl(...) with BLKSSZGET as parameter return 512 */
    BLKSSZGET, & sectorSizeInBytes);
  /** http://man7.org/linux/man-pages/man2/ioctl.2.html :
      "On error, -1 is returned, and errno is set appropriately." */
  if( retVal == -1 ) {
    sectorSizeInBytes = 0;
  }
//  else
//    deviceSizeInBytes = sectorSize * deviceSizeInBytes;
  close(fileDescriptor);
  return sectorSizeInBytes;
}
