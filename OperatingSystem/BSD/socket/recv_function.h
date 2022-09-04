///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDskt_recv_function_h
#define TU_Bln361095cmnSrcBSDskt_recv_function_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Berlin361095MicrosoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef TU_Berlin361095MicrosoftWindows
/** http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-recv :
 *  "Header winsock.h (include Winsock2.h)"*/
  #include <Winsock2.h>
#else
/** http://pubs.opengroup.org/onlinepubs/007904975/functions/recv.html :
 *  section "SYNOPSIS" : "#include <sys/socket.h>" */
  #include <sys/socket.h>
#endif
#endif///TU_Bln361095cmnSrcBSDskt_recv_function_h
