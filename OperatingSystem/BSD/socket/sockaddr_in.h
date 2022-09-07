///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDskt_sockaddr_in_h
#define TU_Bln361095cmnSrcBSDskt_sockaddr_in_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Bln361095MicroSoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef __linux__
 /** http://pubs.opengroup.org/onlinepubs/009695399/basedefs/netinet/in.h.html :
  * "The <netinet/in.h> header shall define the sockaddr_in structure" */
  #include <netinet/in.h>///struct sockaddr_in
#endif
#ifdef TU_Bln361095MicroSoftWindows
  //#include <winsock2.h>///for definitions in Ws2ipdef.h
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-sockaddr_in
 * : "Header winsock.h (include Ws2ipdef.h)" */
  ///"ws2ipdef.h" (lower-case letters) in 64 bit MinGW / TDM-GCC
  #include <ws2ipdef.h>///struct sockaddr_in
#endif

#endif///#ifndef TU_Bln361095cmnSrcBSDskt_sockaddr_in_h
