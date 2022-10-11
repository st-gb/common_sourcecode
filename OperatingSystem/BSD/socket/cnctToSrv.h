///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
/**File name is "cnnctToSrv.h" because:
 * cnct=connect http://www.allacronyms.com/connect/abbreviated
 * Srv=server:http://www.abbreviations.com/abbreviation/server
 * .h because it can be compiled as both C and C++.*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
#ifdef TU_Bln361095usePrgmInclGrd 
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Bln361095cmnSrcBSDskt_cnctToSrv_h
  #define TU_Bln361095cmnSrcBSDskt_cnctToSrv_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Bln361095BSDsktDef,TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd
#include "socket.h"
#include <compiler/force_inline.h>///TU_Bln361095frcInln

///2 functions for either old-style IPv4 or newer IPv4 and IPv6

#if defined TU_Bln361095IPv4 || defined TU_Bln361095autoIPv\
  /**Also define IP version 4 function if IP version 6 is not defined*/\
  || ! defined TU_Bln361095IPv4or6

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
#include "sockaddr_in.h"///struct sockaddr_in

TU_Bln361095BSDsktNmSpcBgn

/** No IPv6 possible with this function. sockaddr_in is for IPv4:
* http://docs.microsoft.com/de-de/windows/win32/api/ws2def/ns-ws2def-sockaddr_in
 * "An IN_ADDR structure that contains an IPv4 transport address."
 * @return -1 on error, else the client? socket file descriptor*/
TU_Bln361095frcInln int TU_Bln361095BSDsktIPv4Def(CnctToSrv)(
  const int sktFileDesc,
  ///Use pointer to avoid copying the struct's 4 member variables.
  struct sockaddr_in * p_srvSockAddr)
{
  ///https://www.ibm.com/docs/en/i/7.1?topic=clients-example-ipv4-ipv6-client
  const int retVal = connect(sktFileDesc,
    /** http://en.wikipedia.org/wiki/Berkeley_sockets#Client :
     * "struct sockaddr_in *" is casted to "struct sockaddr *"*/
    (struct sockaddr *) p_srvSockAddr,///const struct sockaddr *
    sizeof(p_srvSockAddr) );
  return retVal;
}
TU_Bln361095BSDsktNmSpcEnd
#endif///IPv 4 or auto

///Some IPv6 functions not available in 32 bit MinGW->compilation error.
#if defined TU_Bln361095IPv4or6 || defined TU_Bln361095autoIPv\
  /**Also define IP version 6 function if IP version 4 is not defined*/\
  || ! defined TU_Bln361095IPv4

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
#include "addrinfo.h"///struct addrinfo
#include "GetLastError.h"///TU_Bln361095BSDsktUse(GetLastError)

TU_Bln361095BSDsktNmSpcBgn

/**IPv6 possible with this function.
 * @return return code of connect(...) : -1 on error, 0=success:
 *  http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html :
 *  "Upon successful completion, connect() shall return 0; otherwise, -1 shall
 *  be returned and errno set to indicate the error." */
TU_Bln361095frcInln int TU_Bln361095BSDsktIPv4or6Def(CnctToSrv)(
  const int socketFileDesc,
/**http://docs.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfoa
 * : "IPv4 and IPv6" */
  ///"addrinfo" is defined in 32 bit MinGW? (version 5.3.0-2) independent of _WIN32_WINNT
  struct addrinfo ** p_p_addrInfo)
{
  const int retVal = connect(socketFileDesc,
    /**see http://man7.org/linux/man-pages/man3/getaddrinfo.3.html ,section
     * "EXAMPLES", "Client program": member variables "ai_addr" (data type
     * "struct sockaddr *") and "ai_addrlen" (data type "socklen_t") of
     * "struct addrinfo" passed to "connect(...)"*/
    (* p_p_addrInfo)->ai_addr,///const struct sockaddr *
    (* p_p_addrInfo)->ai_addrlen);
/** http://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect
 * :"With a nonblocking socket, the connection attempt cannot be completed
 *  immediately. In this case, connect will return SOCKET_ERROR, and
 *  WSAGetLastError will return WSAEWOULDBLOCK."*/
  if(retVal != 0)
    return TU_Bln361095BSDsktUse(GetLastError);
  return retVal;
}
TU_Bln361095BSDsktNmSpcEnd
#endif///IPv 4, 6 or auto

#endif///#ifndef TU_Bln361095cmnSrcBSDskt_cnctToSrv_h
