///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers,
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDskt_getaddrinfo_h
#define TU_Bln361095cmnSrcBSDskt_getaddrinfo_h

#ifdef __linux__
///http://pubs.opengroup.org/onlinepubs/9699919799/functions/getaddrinfo.html :
 #include <sys/socket.h>
 #include <netdb.h>
#else
  ///TU_Bln361095MicrosoftWindows
  #include <OperatingSystem/Windows/MicrosoftWindows.h>
#endif

#if __MINGW32__ && ! __MINGW64__/**If 32 bit MinGW*/
  /**"getaddrinfo" is only declared in "include/ws2tcpip.h" of 32 bit MinGW if
   * "_WIN32_WINNT >= 0x0501"*/
  #if _WIN32_WINNT < 0x0501
   #define getaddrinfoMayBeDeclPrgmMsg \
    #pragma message "getaddrinfo" is not declared.
    #define TU_Bln361095BSDskt_getaddrinfoNotDecl
  #else
    #define getaddrinfoMayBeDecl
  #endif
#endif
#ifdef __linux__
  #define getaddrinfoMayBeDecl
#endif

#ifdef TU_Bln361095MicrosoftWindows
///http://docs.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
  #include "ws2tcpip.h"///getaddrinfo(...)
#endif

#endif///TU_Bln361095cmnSrcBSDskt_getaddrinfo_h
