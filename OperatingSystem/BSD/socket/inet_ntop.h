///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDskt_inet_ntop_h
#define TU_Bln361095cmnSrcBSDskt_inet_ntop_h

#ifdef __linux__
  /** http://pubs.opengroup.org/onlinepubs/009604499/functions/inet_ntop.html :
   *  "#include <arpa/inet.h>" */
  #include <arpa/inet.h>///inet_ntop(...)
#endif
///<=>32 bit MinGW (64 bit if __MINGW32__ && __MINGW64__)
#ifdef __MINGW32__ && ! defined __MINGW64__
  #pragma message("If compiling with MinGW32 <ws2tcpip.h> may not contain \
inet_ntop")
  #define inet_ntopInclInfoPrgmMsg \
    _Pragma("message \"If compiling with MinGW 32 bit <ws2tcpip.h> may not \
contain inet_ntop(...) function (proved for version 9.2.0)\"")
/** http://docs.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-inet_ntop
 *  http://www.gnu.org/software/gnulib/manual/html_node/inet_005fntop.html :
 *  : "Header 	ws2tcpip.h" */
  #include <ws2tcpip.h>///inet_ntop(...)
#endif

#endif///#ifndef TU_Bln361095cmnSrcBSDskt_inet_ntop_h
