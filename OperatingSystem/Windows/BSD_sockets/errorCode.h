///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Bln361095cmnSrcOpSysWinBSDskt_getLastError_h
  #define TU_Bln361095cmnSrcOpSysWinBSDskt_getLastError_h

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
/**TU_Bln361095BSDsktDef,TU_Bln361095BSDsktUse,TU_Bln361095BSDsktNmSpcBgn,
 * TU_Bln361095BSDsktNmSpcEnd*/
#include <OperatingSystem/BSD/socket/socket.h>
///enum TU_Bln361095BSDsktUse(errorCodes)
#include <OperatingSystem/BSD/socket/GetLastError.h>

/**
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsagetlasterror
* :"Header 	winsock.h (include Winsock2.h)"*/
#include <Winsock2.h>///WSAGetLastError()

TU_Bln361095BSDsktNmSpcBgn

/**Translate Operating System error code to common Operating Sytem-independent
 *  error code to use as unified code.*/
enum TU_Bln361095BSDsktUse(errorCodes) TU_Bln361095BSDsktDef(UnifyErrorCode)(
  const int errorCode)
{
/**Error codes < 10035 are the same as for "errno" under Linux except they are
 * shifted by WSABASEERR (10000L) MinGW/TDM-GCC:include/winerror.h /
http://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2
 * Microsoft Windows: | Linux:
 * include/winerror.h | "errno-base.h"
 * -------------------+------------
 * WSAEINTR  10004    | EINTR   4
 * WSAEBADF  10009    | EBADF   9
 * WSAEACCES 10013    | EACCES 13
 * WSAEFAULT 10014    | EFAULT 14
 * WSAEINVAL 10022    | EINVAL 22
 * WSAEMFILE 10024    | EMFILE 24
 * "#define WSAECONNREFUSED 			__WSA_ERRNO(   61 )"
 * "#define WSAEINPROGRESS				__WSA_ERRNO(   36 )"
 * "#define __WSA_ERRNO(N)  		 	 (WSABASEERR + (N))
 *  #define WSABASEERR			  				10000L"
 http://www.on-time.com/rtos-32-docs/rtip-32/reference-manual/error-codes.htm :
 "ECONNREFUSED (107)" "EINPROGRESS (112)" */
  switch(errorCode){
   case WSAECONNREFUSED:
     return TU_Bln361095BSDsktUse(connRefused);
   case WSAEINPROGRESS:
     return TU_Bln361095BSDsktUse(inProgress);
   case WSAETIMEDOUT:
     return TU_Bln361095BSDsktUse(timedOut);
  }
  return TU_Bln361095BSDsktUse(otherError);
}

/** Get last BSD sockets/Windows sockets error
 * @return WSAGetLastError() to be able to print/output in many languages via
 *   FormatMessage(...)*/
TU_Bln361095frcInln int TU_Bln361095BSDsktDef(GetLastError)()
{
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsagetlasterror
 * -"Minimum supported client  Windows 8.1, Windows Vista [desktop apps | UWP
 *  apps"
 * -"Minimum supported server  Windows Server 2003 [desktop apps | UWP apps]" */
  return WSAGetLastError();
}

TU_Bln361095BSDsktNmSpcEnd

#endif///! defined TU_Bln361095cmnSrcOpSysWinBSDskt_getLastError_h