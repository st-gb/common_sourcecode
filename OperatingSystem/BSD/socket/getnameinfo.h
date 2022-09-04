///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDsktInclGetNmInfo
#define TU_Bln361095cmnSrcBSDsktInclGetNmInfo

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Berlin361095MicrosoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef __linux__
  /** http://linux.die.net/man/3/getnameinfo :
   * "#include <sys/socket.h>
   *  #include <netdb.h>" */
   #include <sys/socket.h>
   #include <netdb.h>
#endif

#ifdef TU_Berlin361095MicrosoftWindows
  #if __MINGW32__//&& __GNUC__ <= 9
//    #define _WIN32_WINNT 0x0501
    #if(_WIN32_WINNT < 0x0501 )
//      #pragma message "_WIN32_WINNT < 0x0501"
      #define getnameinfoInclInfo \
        /*_Pragma("_WIN32_WINNT:" _WIN32_WINNT)*/ \
        _Pragma("message \"If compiling with MinGW ws2tcpip.h may not contain \
getnameinfo(...) function because _WIN32_WINNT is < 0x0501 inside this file\"")
      #define getnameinfoNotDecl
    #else
//      #pragma message "_WIN32_WINNT >= 0x0501"
    #endif
  #endif
  /** http://docs.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-getnameinfo
   *  : "Header 	ws2tcpip.h"
   *  "Minimum supported client 	Windows 8.1, Windows Vista"
   * Available in MinGW if _WIN32_WINNT >= 0x0501 before including
   * <ws2tcpip.h> */
  #include <ws2tcpip.h>///getnameinfo(...)
#endif
#ifndef getnameinfoInclInfo
  #define getnameinfoDecl
  #define getnameinfoInclInfo/**Empty definition*/
#endif

#endif///TU_Bln361095cmnSrcBSDsktInclGetNmInfo
