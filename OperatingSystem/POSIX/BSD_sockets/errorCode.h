///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
/** This file belongs into POSIX folder because "errno" conforms to POSIX:
 * http://linux.die.net/man/3/errno */

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcOpSysPOSIX_BSDskt_errorCode_h
#define TU_Bln361095cmnSrcOpSysPOSIX_BSDskt_errorCode_h

///Standard C header files:
#include <errno.h>///errno

#include <netdb.h>///gai_strerror(...), hstrerror(...)

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
///TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd
#include <OperatingSystem/BSD/socket/socket.h>
//enum TU_Bln361095BSDsktUse(errorCodes)
#include <OperatingSystem/BSD/socket/GetLastError.h>

TU_Bln361095BSDsktNmSpcBgn

/**Force inlining to avoid multiple definitions of this function when linking->
 * compiler error.*/
/**@return Operating System-specific error code because so we can generate
 * language messages from it easily*/
TU_Bln361095frcInln int
  TU_Bln361095BSDsktDef(GetLastError)()
{
  return errno;
}

TU_Bln361095frcInln int TU_Bln361095BSDsktDef(GetLastHostError)()
{
  return h_errno;
}

/**Force inlining to avoid multiple definitions of this function when linking->
 * compiler error.*/
/**Unifies the error code among different implementations (Microsoft Windows,
 * POSIX [,...])*/
TU_Bln361095frcInln enum TU_Bln361095BSDsktUse(ErrorCodes)
 TU_Bln361095BSDsktDef(UnifyErrorCode)(
  const int BSDsktErrorCode)
{
  switch(BSDsktErrorCode){
   case ECONNREFUSED:
     return TU_Bln361095BSDsktUse(ConnRefused);
   case EHOSTUNREACH:
     return TU_Bln361095BSDsktUse(NoRouteToHost);
   case EINPROGRESS:
     return TU_Bln361095BSDsktUse(InProgress);
   case ETIMEDOUT:
     return TU_Bln361095BSDsktUse(TimedOut);
//   case EAFNOSUPPORT:///Happened in "connect(...)" with IPv6 after
//   case EINVAL:///Happened in "connect(...)" with IPv6 after
  }
  return TU_Bln361095BSDsktUse(OtherError);
}

TU_Bln361095BSDsktNmSpcEnd

#endif///#ifndef TU_Bln361095cmnSrcOpSysPOSIX_BSDskt_errorCode_h
