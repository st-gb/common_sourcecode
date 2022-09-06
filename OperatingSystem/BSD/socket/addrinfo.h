///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Berlin361095cmnSrcBSDskt_addrinfo_h
#define TU_Berlin361095cmnSrcBSDskt_addrinfo_h

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///TU_Bln361095MicroSoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef __linux__
  #include <netdb.h>///struct addrinfo
#endif

#ifdef _WIN32
/**http://docs.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfoa
 * : "Header 	ws2def.h"*/
  #include <ws2def.h>///struct addrinfo
#endif

#endif///#ifndef TU_Berlin361095cmnSrcBSDskt_addrinfo_h
