///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDskt_inet_ntoa_h
#define TU_Bln361095cmnSrcBSDskt_inet_ntoa_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Berlin361095MicrosoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef __linux__
/** http://pubs.opengroup.org/onlinepubs/009695399/functions/inet_addr.html
 *  "#include <arpa/inet.h> [...] char *inet_ntoa(struct in_addr in);" */
  #include <arpa/inet.h>///inet_ntoa(...)
#endif
#ifdef TU_Berlin361095MicrosoftWindows
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-inet_ntoa
 * "Header 	winsock2.h (include Winsock2.h, Winsock.h)" */
  #include <winsock2.h>///inet_ntoa(...)
#endif

#endif///#ifndef TU_Bln361095cmnSrcBSDskt_inet_ntoa_h
