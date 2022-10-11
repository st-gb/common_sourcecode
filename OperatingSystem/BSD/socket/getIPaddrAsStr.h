///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Bln361095cmnSrcBSDskt_getIPaddrAsStr_h
  #define TU_Bln361095cmnSrcBSDskt_getIPaddrAsStr_h

///Standard C header files:
#include <stddef.h>///NULL
#include <string.h>///strcpy(...)

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///TU_Bln361095BSDsktDef,TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd
#include "socket.h"
#include <compiler/force_inline.h>///TU_Bln361095frcInln" preprocessor macro
#include <OperatingSystem/BSD/socket/errorCode.h>
///OperatingSystem::BSD::sockets::GetLastError();
#include <OperatingSystem/BSD/socket/GetLastError.h>

#ifdef __cplusplus
  #define TU_Bln361095BSDsktGetIPaddrAsStrDef(suffix) \
   TU_Bln361095BSDsktDef(suffix)
  #define TU_Bln361095BSDsktGetIPaddrAsStrUse(suffix) \
   TU_Bln361095BSDsktDef(GetIPaddrAsStrRslt :: suffix)
  #define GetIPaddrAsStrRsltNmSpBgn namespace GetIPaddrAsStrRslt{
  #define GetIPaddrAsStrRsltNmSpEnd }
#else
  #define TU_Bln361095BSDsktGetIPaddrAsStrDef(suffix) \
   TU_Bln361095BSDsktDef(GetIPaddrAsStrRslt##suffix)
  #define TU_Bln361095BSDsktGetIPaddrAsStrUse(suffix) \
   TU_Bln361095BSDsktDef(GetIPaddrAsStrRslt##suffix)
  #define GetIPaddrAsStrRsltNmSpBgn
  #define GetIPaddrAsStrRsltNmSpEnd
#endif

GetIPaddrAsStrRsltNmSpBgn

enum TU_Bln361095BSDsktDef(GetIPaddrAsStrRslt){
  TU_Bln361095BSDsktGetIPaddrAsStrDef(Success) = 0,
///Insuf=INSUFficient: http://www.abbreviations.com/abbreviation/Insufficient
///Buf=BUFfer: http://www.abbreviations.com/abbreviation/buffer
  TU_Bln361095BSDsktGetIPaddrAsStrDef(InsuffBuf),///INSUFFucient BUFfer
  TU_Bln361095BSDsktGetIPaddrAsStrDef(inet_ntoaFailed),
  TU_Bln361095BSDsktGetIPaddrAsStrDef(UnsuppProto)///UNSUPPorted PROTOcol
};

GetIPaddrAsStrRsltNmSpEnd

/**The author's matriculation number is independent of any website/URL (this may
 * change). Specify this as compiler definition like
 * "-DTU_Berlin361095IPv=4" for g++ or indirectly if using CMake as its
 * parameter: "-DTU_Berlin361095IPv4"*/
///For C++ function overloading exists, so we can include both functions.
#if defined TU_Bln361095IPv4 || defined TU_Bln361095autoIPv ||\
  ! defined TU_Bln361095IPv4or6//defined __cplusplus)

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include "sockaddr_in.h"///struct sockaddr_in
#include "inet_ntoa.h"///inet_ntoa(...)

#ifdef TU_Bln361095MicroSoftWindows
  //TODO test: under MS Windows the return value may be NULL.
  #define inet_ntoaFailureRetCode NULL
#else
/** http://pubs.opengroup.org/onlinepubs/9699919799/functions/inet_ntoa.html :
 * "Upon successful completion, inet_addr() shall return the Internet address.
 *  Otherwise, it shall return ( in_addr_t)(-1)."*/
  #define inet_ntoaFailureRetCode (in_addr_t)(-1)
#endif

TU_Bln361095BSDsktNmSpcBgn

//#pragma message "C++ or IPv4"
#define FnDefined
/**@param p_addrStr filled with IP address character string if {@link
 *  numAddrCharStrChars} is sufficient.
 *  The result format is <num1>.<num2>.<num3>.<num4>, for example: "127.0.0.1"
 * @return
 *  TU_Bln361095BSDsktGetIPaddrAsStrUse(Success): success
 *  TU_Bln361095BSDsktGetIPaddrAsStrUse(inet_ntoaFailed): calling function
 *   "inet_ntoa" failed.
 *  TU_Bln361095BSDsktGetIPaddrAsStrUse(InsuffBuf): {@link numAddrCharStrChars}
 *   is less than needed for copying the result character string of function
 *   "inet_ntoa" to {@link p_addrStr}*/
TU_Bln361095frcInln int
  /**Name as "getIPaddrAsStr" for the "C" programming language that has no
   * function overloading".*/
  TU_Bln361095BSDsktIPv4Def(GetIPaddrAsStr)(
  const struct sockaddr_in * const p_sockaddr_in,
  char ** p_addrStr,
  unsigned numAddrCharStrChars)
{
  char * p_chInetStdDotNotatedAddr =
/** http://pubs.opengroup.org/onlinepubs/9699919799/functions/inet_ntoa.html :
 * "The inet_ntoa() function shall convert the Internet host address specified
 *  by _in_ to a string in the Internet standard dot notation."*/
/**
http://learn.microsoft.com/en-us/windows/win32/api/wsipv6ok/nf-wsipv6ok-inet_ntoa
 * : "The inet_ntoa function converts an (Ipv4) Internet network address into an
 * ASCII string in Internet standard dotted-decimal format."*/
   inet_ntoa(
/** http://docs.oracle.com/cd/E36784_01/html/E36875/inet-ntoa-3socket.html :
 * " The [...] inet_ntoa() functions can only manipulate IPv4 addresses."*/
///https://pubs.opengroup.org/onlinepubs/9699919799/functions/inet_ntoa.html
    /**struct in_addr in*/ ///"in_addr": 4 byte
     p_sockaddr_in->sin_addr
     );
  if( p_chInetStdDotNotatedAddr == /**Needs to be casted to avoid g++ error
    * "ISO C++ forbids comparison between pointer and integer [-fpermissive]"*/
    (char *) inet_ntoaFailureRetCode)
    return TU_Bln361095BSDsktGetIPaddrAsStrUse(inet_ntoaFailed);
  if(numAddrCharStrChars <= strlen(p_chInetStdDotNotatedAddr) )
    return TU_Bln361095BSDsktGetIPaddrAsStrUse(InsuffBuf);
/**
http://learn.microsoft.com/en-us/windows/win32/api/wsipv6ok/nf-wsipv6ok-inet_ntoa
 *, "Remarks" section: "The string returned is guaranteed to be valid only until
 * the next Windows Sockets function call is made within the same thread.
 * Therefore, the data should be copied before another Windows Sockets call is
 * made."*/
  strcpy(*p_addrStr, p_chInetStdDotNotatedAddr);
  return TU_Bln361095BSDsktGetIPaddrAsStrUse(Success);
}
TU_Bln361095BSDsktNmSpcEnd
#endif

///Only if compiled as C++ we can have a second function with the same name.
#if defined TU_Bln361095IPv4or6 || defined TU_Bln361095autoIPv ||\
  ! defined TU_Bln361095IPv4//\
 //&& (defined __cplusplus || not defined(FnDefined) )
//#pragma message "C++ or IPv6"

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
#include "addrinfo.h"///struct addrinfo
#include "inet_ntop.h"///inet_ntop(...)

TU_Bln361095BSDsktNmSpcBgn

/**@brief Gets character string from binary representation of Internet Protocol
 *  address version 4 or 6.
 *  With MinGW 32 bit inet_ntop(...) may not be declared in <ws2tcpip.h>.
 * @param p_p_addrInfo Internet Protocol address in binary representation
 * @param pp_addrStr : dereferenced string is filled with character string
 *  representation of {@link p_p_addrInfo}
 *  Use buffer size INET6_ADDRSTRLEN (on heap or stack) for dereferenced version
 *  of this parameter (*p_p_addrInfo) to ensure it is sufficient.
 * @param numAddrCharStrChars
 *  Use INET6_ADDRSTRLEN as value and as buffer size for dereferenced {@link
 *  pp_addrStr} to ensure it is sufficient:
 *  http://pubs.opengroup.org/onlinepubs/009604499/functions/inet_ntop.html :
 *  "INET6_ADDRSTRLEN characters for IPv6"
 * @return 0: success, else: for Linux/unixoid Operating Systems: "errno", for
 *  Microsoft Windows WSAGetLastError()*/
TU_Bln361095frcInln int
  /**Name as "getIPaddrAsStr" for the "C" programming language that has no
   * function overloading".*/
  TU_Bln361095BSDsktIPv4or6Def(GetIPaddrAsStr)(
  addrinfo ** p_p_addrInfo,
  char ** pp_addrStr,
  unsigned numAddrCharStrChars,
  TU_Bln361095BSDsktRsltTypeUse(RsltType) * p_rsltType
  )
{
  const void *__restrict __cp;
  switch( (*p_p_addrInfo)->ai_family){
   case AF_INET6:
    ///http://stackoverflow.com/questions/38848281/inet-ntop-printing-incorrect-ipv6-address
    __cp = & ( (struct sockaddr_in6*) (*p_p_addrInfo)->ai_addr)->sin6_addr;
    break;
   case AF_INET:
    __cp = & ((sockaddr_in const *)(*p_p_addrInfo)->ai_addr)->sin_addr;
    break;
   default:
    *p_rsltType = TU_Bln361095BSDsktRsltTypeUse(GetIPaddrAsStr);
    return TU_Bln361095BSDsktGetIPaddrAsStrUse(UnsuppProto);
  }
//  inet_ntopInclInfo
/**http://pubs.opengroup.org/onlinepubs/009604499/functions/inet_ntop.html :
 * "const char *inet_ntop"
 * "The inet_ntop() function shall return a pointer to the buffer containing the
 * text string if the conversion succeeds, and NULL otherwise, and set errno to
 * indicate the error."*/
  const char * inet_ntopRslt =
  /** http://pubs.opengroup.org/onlinepubs/009604499/functions/inet_ntop.html :
   * "The inet_ntop() function shall convert a numeric address into a text
   *  string suitable for presentation." */
/** http://en.wikipedia.org/wiki/Berkeley_sockets#gethostbyname_and_gethostbyaddr
 *  "inet_pton" is not BSD but POSIX?*/
    inet_ntop(
    (*p_p_addrInfo)->ai_family,///"int __af" (address family)
//      p_addrInfo->ai_addr->sa_data,
/**http://stackoverflow.com/questions/1966687/bogus-ip-address-from-getaddrinfo-inet-ntop
* from ""Xymostech" at Dec 27 '09 at 19:09 for 2nd parameter*/
    __cp,///const void *__restrict __cp,
    *pp_addrStr,///char *__restrict __buf,
    /*INET6_ADDRSTRLEN*/numAddrCharStrChars///socklen_t __len
    );
  if(
 /** http://pubs.opengroup.org/onlinepubs/009604499/functions/inet_ntop.html :
  * "The inet_ntop() function shall return a pointer to the buffer containing
  * the text string if the conversion succeeds, and NULL otherwise, and set
  * errno to indicate the error." */
    inet_ntopRslt != NULL
    )
  {
    *p_rsltType = TU_Bln361095BSDsktRsltTypeUse(GetIPaddrAsStr);
    return TU_Bln361095BSDsktGetIPaddrAsStrUse(Success);
  }
  /**http://pubs.opengroup.org/onlinepubs/009604499/functions/inet_ntop.html :
   * "The inet_ntop() function shall return [...] if the conversion succeeds,
   * and NULL otherwise, and set errno to indicate the error."*/
/**http://docs.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-inet_ntop
 * : "Otherwise, a value of NULL is returned, and a specific error code can be
 * retrieved by calling the WSAGetLastError for extended error information."*/
  *p_rsltType = TU_Bln361095BSDsktRsltTypeUse(_errno);
  return TU_Bln361095BSDsktUse(GetLastError)();
}
TU_Bln361095BSDsktNmSpcEnd
#endif

#endif///#ifndef TU_Bln361095cmnSrcBSDskt_getIPaddrAsStr_h
