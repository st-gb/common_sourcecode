///(c)from 2020 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Bln361095cmnSrcBSDskt_createSkt_h
  #define TU_Bln361095cmnSrcBSDskt_createSkt_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
#include <compiler/force_inline.h>///"TU_Bln361095frcInln" preprocessor macro
///TU_Bln361095MicrosoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>
///TU_Bln361095BSDsktDef,TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd
#include "socket.h"
#include "socket_function.h"///socket(...)

#ifdef __cplusplus
TU_Bln361095BSDsktNmSpcBgn
#else
static///Needed for C
#endif
/**Used by client and server for socket creation.
 * @param protoFam address family/protocol family, for example AF_INET
 *  (Address Family InterNET) for IP protocol version 4
 * @param socketType for example SOCK_STREAM for TCP or SOCK_DGRAM for UDP
 * @return error code: either WSAGetLastError() for Microsoft Windows or "errno"
 *  This enables language-specific error messages via FormatMessage(...) for
 *  Microsoft Windows:
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsagetlasterror
 *  and strerror_l(...) for Linux:
 *  http://man7.org/linux/man-pages/man3/strerror.3.html */
///Make inline because only 1 function call inside->no size benefit.
TU_Bln361095frcInln int TU_Bln361095BSDsktDef(CreateSkt)(
  const int protoFam,
  const int socketType,
  const int proto,
  int * const p_socketFileDesc)
{
  /** http://pubs.opengroup.org/onlinepubs/009695399/functions/socket.html :
   * "Upon successful completion, socket() shall return a non-negative integer, 
   * the socket file descriptor." */
  const int sktFileDesc =
/** http://pubs.opengroup.org/onlinepubs/009695399/functions/socket.html :"The
 * socket() function shall create an unbound socket in a communications domain,
 * and return a file descriptor that can be used in later function calls that
 * operate on sockets."*/
    socket(
    /**http://man7.org/linux/man-pages/man2/socket.2.html:
    * AF_INET for IPv4 Internet protocols */protoFam,
    socketType,///e.g. UDP oder TCP
    /** socket.h : "If PROTOCOL is zero, one is chosen automatically." */
    /**http://man7.org/linux/man-pages/man2/socket.2.html: 
     "Normally only a single protocol exists to support a
       particular socket type within a given protocol family, in which case
       protocol can be specified as 0."*/
    proto);
#ifdef TU_Bln361095MicrosoftWindows
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
 * :"If no error occurs [...]. Otherwise, a value of INVALID_SOCKET is returned,
 *  and a specific error code can be retrieved by calling WSAGetLastError."*/
  if(*p_socketFileDesc == INVALID_SOCKET)
	  return WSAGetLastError();
#else
/** http://pubs.opengroup.org/onlinepubs/009695399/functions/socket.html :
 * "Upon successful completion [...]. Otherwise, a value of -1 shall be returned 
 *  and errno set to indicate the error." */
  if(*p_socketFileDesc == -1)
	  return errno;
#endif
  return 0;
}

TU_Bln361095BSDsktNmSpcEnd

#endif///! defined TU_Bln361095cmnSrcBSDskt_createSkt_h