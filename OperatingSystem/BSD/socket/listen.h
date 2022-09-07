///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Berlin361095cmnSrcBSDskt_listen_h
#define TU_Berlin361095cmnSrcBSDskt_listen_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Bln361095MicroSoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#if __linux__
  /** http://pubs.opengroup.org/onlinepubs/009695399/functions/listen.html :
   * includes <sys/socket.h>*/
  #include <sys/socket.h>///listen(...)
#endif
#ifdef TU_Bln361095MicroSoftWindows
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen
 * "Header 	winsock2.h"*/
  #include <winsock2.h>///listen(...)
#endif

#endif///#ifndef TU_Berlin361095cmnSrcBSDskt_listen_h
