/** File:   GetNumberOfLogicalCPUcores.h
 * Author: sg
 * Created on 12. September 2017, 19:38b */
#pragma once
//#ifndef GETNUMBEROFLOGICALCPUCORES_H
//#define GETNUMBEROFLOGICALCPUCORES_H

#include <winbase.h> //GetSystemInfo(...)

#ifdef __cplusplus
namespace OperatingSystem
{
  #define INLINE inline
#else //#ifdef __cplusplus
  #define INLINE /** -> empty (C does not know inline?!) */
#endif //#ifdef __cplusplus
  INLINE int GetNumberOfLogicalCPUcores()
  {
    SYSTEM_INFO SystemInfo;
    //https://stackoverflow.com/questions/2619198/how-to-get-number-of-cores-in-win32
    GetSystemInfo( & SystemInfo);
    return SystemInfo.dwNumberOfProcessors;
  }
#ifdef __cplusplus
}
#endif

//#endif /* GETNUMBEROFLOGICALCPUCORES_H */
