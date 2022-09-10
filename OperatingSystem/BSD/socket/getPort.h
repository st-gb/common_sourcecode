///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Berlin361095cmnSrcBSDskt_getPort_h
#define TU_Berlin361095cmnSrcBSDskt_getPort_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
#include <hardware/CPU/fastest_data_type.h>///TU_Bln361095CPUuse(FaststUint)
/**TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd,
 * TU_Bln361095BSDsktIPv4Def,TU_Bln361095BSDsktIPv4or6Def*/
#include <OperatingSystem/BSD/socket/socket.h>

#if TU_Bln361095IPv4 || TU_Bln361095autoIPv || ! defined(TU_Bln361095IPv4or6)
#include "sockaddr_in.h"///struct sockaddr_in

/**Use C++ to take advantage of function overloading: depending on the
 * parameter either of the function is used. (->Can't be compiled as C)*/
TU_Bln361095BSDsktNmSpcBgn

///@return client? port number
TU_Bln361095frcInln TU_Bln361095CPUuse(FaststUint) TU_Bln361095BSDsktIPv4Def(
  GetPort)(
  const struct sockaddr_in & sockAddr)
{
  /**See http://www.steves-internet-guide.com/tcpip-ports-sockets :
   * This is the ephemeral/client port number.*/
  return sockAddr.sin_port;
}
TU_Bln361095BSDsktNmSpcEnd
#endif///IPv 4 or auto

#if TU_Bln361095IPv4or6 || TU_Bln361095autoIPv || ! defined(TU_Bln361095IPv4)
#include "addrinfo.h"///struct addrinfo

TU_Bln361095BSDsktNmSpcBgn

///@return server port number
TU_Bln361095frcInln TU_Bln361095CPUuse(FaststUint) TU_Bln361095BSDsktIPv4or6Def(
  GetPort)(
  const struct addrinfo * const p_addrInfo)
{
  TU_Bln361095CPUuse(FaststUint) port;
  /**getnameinfo(...) can't be used to get the port number:it fills "__serv"
   * with the service name corresponding to the port ("e.g. "ssh", not with
   * port number.*/
  ///1st 2 bytes of "struct sockaddr.sa_data" are port.
//  fastestUnsignedDataType port = *((uint16_t *) p_addrInfo->ai_addr->sa_data);
//  port = ntohs(port);
  switch(p_addrInfo->ai_addr->sa_family){
   case AF_INET:
    port = ntohs( ( (struct sockaddr_in*)p_addrInfo->ai_addr)->sin_port);
    break;
   case AF_INET6:
///http://stackoverflow.com/questions/2371910/how-to-get-the-port-number-from-struct-addrinfo-in-unix-c
    port = ntohs( ( (struct sockaddr_in6*)p_addrInfo->ai_addr)->sin6_port);
    break;
  }
  return port;
}
TU_Bln361095BSDsktNmSpcEnd
#endif///IPv 4, 6 or auto

#endif///#ifndef TU_Berlin361095cmnSrcBSDskt_getPort_h
