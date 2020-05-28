#pragma once

//#include <stdio.h>///FILE
#include <iostream>///std:::ostringstream

#ifdef __cplusplus
namespace dataCarrier{
#endif
uint64_t getNumBwrittenSinceOSstart(const char devName[])///E.g. "sda"
{
  uint64_t numBwrittenSinceOSstart = 0;
//  FILE * p_file = fopen("/proc/diskstats","r");///"iostat /dev/sd?"
  std::ifstream is("/proc/diskstats");
  if(/*p_file*/is.is_open() ){
    int dummy;
//    char dvcName[80];
    std::string devNameFromFile;
//    std::string stdstrNumBwrittenSinceOSstart;
    do{
    //Without /dev/
//    fscanf(p_file, "%d%d%s", dummy, dummy, );
    is >> dummy >> dummy >> devNameFromFile;
    if(/*strcmp(dev)*/ devNameFromFile == devName)
    {
      /**https://www.kernel.org/doc/Documentation/ABI/testing/procfs-diskstats :
       * column 10  is "sectors written" * 512 = bytes written */
//    fscanf(p_file, "%", 
      is >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy >> 
        numBwrittenSinceOSstart;//stdstrNumBwrittenSinceOSstart;
      numBwrittenSinceOSstart *= 512;
      break;
    }
    else
    {
      ///Read until line end.
      std::getline(is, devNameFromFile);
    }
    }while(! is.eof());
    is.close();
  }
  return numBwrittenSinceOSstart;
}
#ifdef __cplusplus
}
#endif
