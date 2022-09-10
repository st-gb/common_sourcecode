///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

/**Include this file after all Stefan Gebauer's(TU Berlin matric.#361095) BSD
 * socket (header) files with IPv4 and IPv4 or 6 versions from his
 * "common_sourcecode" repository have been included. Because then the IP
 * version socket type can be defined after it is known. whether it can be IPv6
 * or not.*/
/**File name comes from:
 * addr=address:http://www.abbreviations.com/abbreviation/address */

///Include guard:http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDskt_SktAddrType_h
#define TU_Bln361095cmnSrcBSDskt_SktAddrType_h

#include <compiler/force_inline.h>///TU_Bln361095frcInln
///TU_Bln361095BSDsktDef,TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd
#include <OperatingSystem/BSD/socket/socket.h>

#include "freeaddrinfo.h"///freeaddrinfo(...),freeaddrinfoNotDecl

///If IPv6 functions in included header files are not available.
#if defined getnameinfoNotDecl || defined addrinfoNotDecl || freeaddrinfoNotDecl
  #define TU_Bln361095IPv4
  #pragma message("IPv set to 4 because >=1 needed IPv6-able functions not declared.")
#endif

#if ! (defined TU_Bln361095IPv4 || defined TU_Bln361095IPv4or6 || \
  defined TU_Bln361095IPv6)
  #ifdef TU_Berlin361095mayUseIPv6BSDsock
    #define TU_Berlin361095IPv6
  #else
    ///IP version 4 is better supported (MinGW 32 bit).
    #define TU_Berlin361095IPv4
  #endif
#endif

/** "TU_Berlin361095IPv" instead of for example "IPv" to avoid name conflicts
 *  with definitions from other included files.
 *  Define as compiler definition.*/
#if defined TU_Bln361095IPv4
#ifdef __cplusplus
  #define TU_Bln361095BSDsktIPvUse(suffix) TU_Bln361095BSDsktUse(suffix)
#else
  #define TU_Bln361095BSDsktIPvUse(suffix) TU_Bln361095BSDsktPrfx(IPv4##suffix)
#endif
///Forward declaration because struct isn't used.
struct sockaddr_in;

TU_Bln361095BSDsktNmSpcBgn

typedef struct sockaddr_in TU_Bln361095BSDsktIPv4Def(SktAddrType);
typedef TU_Bln361095BSDsktIPvUse(SktAddrType) *
  TU_Bln361095BSDsktIPv4Def(SktAddrPtrType);
TU_Bln361095frcInln void TU_Bln361095BSDsktDef(FreeAddr)(const struct
  sockaddr_in sockAddr){/**Empty function definition--correct?*/}

TU_Bln361095BSDsktNmSpcEnd

#else///defined TU_Bln361095IPv4
#ifdef __cplusplus
  #define TU_Bln361095BSDsktIPvUse(suffix) TU_Bln361095BSDsktUse(suffix)
#else
  #define TU_Bln361095BSDsktIPvUse(suffix) /*TU_Bln361095BSDsktPrfx*/\
    TU_Bln361095BSDsktUse(IPv4or6##suffix)
#endif

TU_Bln361095BSDsktNmSpcBgn

/**"struct addrinfo" is available in MinGW's "ws2tcip.h" independent of
 * _WIN32_WINNT.*/
///skt=socket:http://www.abbreviations.com/abbreviation/socket
typedef struct addrinfo * TU_Bln361095BSDsktIPv4or6Def(SktAddrType);
typedef TU_Bln361095BSDsktIPvUse(SktAddrType) * TU_Bln361095BSDsktIPv4or6Def(
  SktAddrPtrType);

TU_Bln361095frcInln void TU_Bln361095BSDsktDef(FreeAddr)(
  struct addrinfo * const p_addrInfo)
{
  freeaddrinfo(p_addrInfo);
}

TU_Bln361095BSDsktNmSpcEnd

#endif///not defined TU_Bln361095IPv4

#endif///TU_Bln361095cmnSrcBSDskt_SktAddrType_h
