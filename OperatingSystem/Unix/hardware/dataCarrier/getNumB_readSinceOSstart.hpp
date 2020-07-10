#pragma once///Include guard
/// specific to Linux/Unix

#include <fstream>///std:::ifstream

#ifdef __cplusplus
namespace dataCarrier{
#endif
///\param devName must be without "/dev/"
uint64_t getNumB_readSinceOSstart(const char devName[])///E.g. "sda"
{
  uint64_t numB_readSinceOSstart = 0;
  std::ifstream is("/proc/diskstats");
  if(is.is_open() ){
    int dummy;
    std::string devNameFromFile;
    do{
    /** https://www.kernel.org/doc/Documentation/ABI/testing/procfs-diskstats :
     * Col 3 is device name */
    is >> dummy >> dummy >> devNameFromFile;
    if(devNameFromFile == devName)
    {
      /**https://www.kernel.org/doc/Documentation/ABI/testing/procfs-diskstats :
       * column 10  is "sectors written" * 512 = bytes written */
      is >> dummy >> dummy >> numB_readSinceOSstart;
      ///iostat output = /proc/diskstats value * 512 /1024 ?
      numB_readSinceOSstart *= 512;
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
  return numB_readSinceOSstart;
}

///\param stdstrDataCarrierPath : e.g. "/dev/sda"
uint64_t getNumB_readSinceOSstart(const std::string & stdstrDataCarrierPath)
{
  std::string dvcName = stdstrDataCarrierPath.substr(stdstrDataCarrierPath.
    rfind("/")+1 );
  return getNumB_readSinceOSstart(dvcName.c_str());
}
#ifdef __cplusplus
}
#endif