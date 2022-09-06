///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Berlin361095cmnSrcBSDskt_bind_h
#define TU_Berlin361095cmnSrcBSDskt_bind_h

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///TU_Bln361095MicroSoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef __linux__
  ///see http://pubs.opengroup.org/onlinepubs/009695399/functions/bind.html
  #include <sys/socket.h>///bind(...)
#endif
#if TU_Bln361095MicroSoftWindows
  /**http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-bind :
   * "winsock.h (include Winsock2.h"*/
  #include <Winsock2.h>
#endif

#endif///#ifndef TU_Berlin361095cmnSrcBSDskt_bind_h
