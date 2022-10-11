/**(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * Created 9.Sep 2022,07:30*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
/**Define on compiler command line,for example for GCC:
 * (see http://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html :)
 * "gcc -D TU_Bln361095UsePrgmInclGuard"*/
#ifdef TU_Bln361095usePrgmInclGrd
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
  /**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Bln361095BSDsktAccept_fn_h
  #define TU_Bln361095BSDsktAccept_fn_h

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///TU_Bln361095BSDsktDef,TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd
#include "socket.h"
///TU_Bln361095MicroSoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef TU_Bln361095MicroSoftWindows
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
  * "(int *)"*/
  TU_Bln361095BSDsktNmSpcBgn
  typedef TU_Bln361095BSDsktDef(addrLenType) int *;
  TU_Bln361095BSDsktNmSpcEnd
#else
  ///http://pubs.opengroup.org/onlinepubs/7908799/xns/syssocket.h.html
  ///Include must be outside of "TU_Bln361095BSDsktNmSpc" scope if C++ compiler
  #include <sys/socket.h>///socklen_t
  TU_Bln361095BSDsktNmSpcBgn
  /** http://pubs.opengroup.org/onlinepubs/009696699/functions/accept.html :
   * "socklen_t *"*/
  typedef socklen_t * TU_Bln361095BSDsktDef(addrLenType);
  TU_Bln361095BSDsktNmSpcEnd
#endif

#endif///#ifndef TU_Bln361095BSDsktAccept_fn_h