/** File:   GetNumberOfCPUcores.h
 * Author: sg
 * Created on 15. Juni 2017, 00:23  */

#ifndef GETNUMBEROFCPUCORES_H
#define GETNUMBEROFCPUCORES_H

/** http://man7.org/linux/man-pages/man3/sysconf.3.html
 *  "CONFORMING TO POSIX.1-2001, POSIX.1-2008".*/

//https://stackoverflow.com/questions/4586405/get-number-of-cpus-in-linux-using-c
#include <unistd.h> //sysconf(...)

#ifdef __cplusplus
namespace OperatingSystem
{
  #define INLINE inline
#else //#ifdef __cplusplus
  #define INLINE /** -> empty (C does not know inline?!) */
#endif //#ifdef __cplusplus
  INLINE int GetNumberOfLogicalCPUcores()
  {
    return sysconf(_SC_NPROCESSORS_ONLN);
  }
#ifdef __cplusplus
}
#endif

#endif /* GETNUMBEROF CPUCORES_H */
