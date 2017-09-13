/** File:   GetNumberOfLogicalCPUcores.h
 * Author: Stefan Gebauer
 * Created on 12. September 2017, 19:35 */

#ifndef GETNUMBEROFLOGICALCPUCORES_H
#define GETNUMBEROFLOGICALCPUCORES_H

#ifdef __unix__
  #include <OperatingSystem/POSIX/GetNumberOfLogicalCPUcores.h>
#endif
#ifdef _WIN32
  #include <Windows/CPU/GetNumberOfLogicalCPUcores.h>
#endif

#endif /* GETNUMBEROFLOGICALCPUCORES_H */

