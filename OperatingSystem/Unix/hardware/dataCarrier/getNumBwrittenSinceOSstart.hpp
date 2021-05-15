#pragma once///Include guard
/// specific to Linux/Unix

//#include <stdio.h>///FILE
#include <fstream>///std:::ifstream

#ifdef __cplusplus
namespace dataCarrier{
#endif
uint64_t getNumBwrittenSinceOSstart(const char devName[])///E.g. "sda"
{
  uint64_t numBwrittenSinceOSstart = 0;
//  FILE * p_file = fopen("/proc/diskstats","r");///"iostat /dev/sd?"
  std::ifstream is("/proc/diskstats");
  if(/*p_file*/is.is_open() ){
    /** Must use data type with high capacity to ensure correct read if number
     * is large?
     * Using "int" data type lead to wrong values like "0" for # bytes written
     * since OS start although the real value was around 667509360 kB.
     * This may be due to the 3rd value after "sda" was too large
     * (~"3459346078") for a _signed_ int
     * Alternative: read as std::string for the unneccesary (until column 10)
     *  space-separated values.*/
    uint64_t dummy;
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

///\brief stdstrDataCarrierPath : e.g. "/dev/sda"
uint64_t getNumBwrittenSinceOSstart(const std::string & stdstrDataCarrierPath)
{
  std::string dvcName = stdstrDataCarrierPath.substr(stdstrDataCarrierPath.
    rfind("/")+1 );
  return getNumBwrittenSinceOSstart(dvcName.c_str());
}
#ifdef __cplusplus
}
#endif
