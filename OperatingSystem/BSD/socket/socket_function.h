///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers,
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDskt_sktfn_h
#define TU_Bln361095cmnSrcBSDskt_sktfn_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Bln361095MicrosoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef TU_Bln361095MicrosoftWindows
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
 * : "Header winsock2.h"*/
 #include <winsock2.h>///socket(...),WSAGetLastError()
#else
/** http://pubs.opengroup.org/onlinepubs/009604499/functions/socket.html :
 *  "include <sys/socket.h>" */
  #include <sys/socket.h>///socket(...)
#endif

#endif//#define TU_Bln361095cmnSrcBSDskt_sktfn_h
