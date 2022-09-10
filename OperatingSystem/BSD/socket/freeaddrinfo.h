///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDskt_freeaddrinfo_h
#define TU_Bln361095cmnSrcBSDskt_freeaddrinfo_h

///TU_Bln361095MicrosoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef __linux__
/** http://pubs.opengroup.org/onlinepubs/009695399/functions/freeaddrinfo.html :
 *  "#include <sys/socket.h>
 *   #include <netdb.h>"*/
//  #include <sys/socket.h>
  #include <netdb.h>///freeaddrinfo(...)
#endif

#ifdef TU_Bln361095MicrosoftWindows
/**"freeaddrinfo" is only available if _WIN32_WINNT >= 0x0501 in <ws2tcip.h>:
 * -in TDM-GCC (for example version 9.2) 32 bit
 * -MinGW (for example version 5.3.0-2) 32 bit
 * "freeaddrinfo" is available in "ws2tcip.h" of (recent) MinGW w64
 * independent of "_WIN32_WINNT"/in any case.*/
///MinGW 32 bit and not MinGW 64 bit<=>32 bit MinGW installation
#if __MINGW32__ && !__MINGW64__
  #define freeaddrinfoNotDecl
#else
/** http://docs.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-freeaddrinfo
 * "Header 	ws2tcpip.h" */
  #include <ws2tcpip.h>
#endif///32 bit MinGW
#endif

#endif///#ifndef TU_Bln361095cmnSrcBSDskt_freeaddrinfo_h
