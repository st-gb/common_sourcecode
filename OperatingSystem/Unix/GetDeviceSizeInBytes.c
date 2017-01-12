/*
 * GetDeviceSize.c
 *
 *  Created on: 22.11.2015
 *      Author: s.gebauer
 */

#include <stdint.h> //uint64_t
#include <sys/ioctl.h> //ioctl(...)
#include <fcntl.h> //O_RDONLY, open(...)
#include <linux/fs.h> //BLKGETSIZE64
#include <unistd.h> //close(...)

/** https://en.wikipedia.org/wiki/Ioctl 
 *   "The ioctl system call first appeared in Version 7 of Unix under that name." 
    uses ioctl(...), so put it in a folder/namespace called "Unix"  */
#ifdef __cplusplus__
//namespace Unix {
#endif

/** @param filePath : e.g. /dev/sda1 
    @return */
uint64_t GetDeviceSizeInBytes(const char * const filePath)
{
  /** From http://www.linuxproblem.org/art_20.html 
      "How to determine the size of a raw device (in a C programm)" */
  int fileDescriptor;
  uint64_t deviceSizeInBytes;//, blockSizeInBytes;

  fileDescriptor = open(filePath, O_RDONLY);
  if( fileDescriptor < 0 )
    return 0;
  /** From http://www.microhowto.info/howto/get_the_size_of_a_linux_block_special_device_in_c.html
   *  "if you require compatibility with very old versions of Linux (prior to
   *  2.4.10) then it may be appropriate to use BLKGETSIZE as a fallback." */
#ifdef __LINUX_MAJOR //< 2 && MINOR < 4
  unsigned long numBlocks = 0;
  /** http://www.linuxproblem.org/art_20.html */
  int retVal = ioctl(fileDescriptor, BLKGETSIZE, & numBlocks);
  if( retVal == -1 ) {
    deviceSizeInBytes = 0;
  }
  else
    deviceSizeInBytes = numBlocks;
  retVal = ioctl(fileDescriptor, BLKBSZGET, & numBlocks);
#else
  /** From http://www.microhowto.info/howto/get_the_size_of_a_linux_block_special_device_in_c.html
   *  : "[...] which is the size in bytes:" */
  int retVal = ioctl(fileDescriptor, BLKGETSIZE64, &deviceSizeInBytes);
#endif
  /** http://man7.org/linux/man-pages/man2/ioctl.2.html : 
   *  "On error, -1 is returned, and errno is set appropriately." */
  if( retVal == -1 ) {
	deviceSizeInBytes = 0;
  }
//  else
//    deviceSizeInBytes = numBlocks * deviceSizeInBytes;
  close(fileDescriptor);
//  printf("Number of blocks: %lu, this makes %.3f GB\n",
//      deviceSizeInBytes,
//   (double)deviceSizeInBytes * 512.0 / (1024 * 1024 * 1024));
  return deviceSizeInBytes;
}
#ifdef __cplusplus__
//} //end namespace
#endif

