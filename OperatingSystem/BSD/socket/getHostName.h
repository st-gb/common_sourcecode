///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDsktGetHostNm_h
#define TU_Bln361095cmnSrcBSDsktGetHostNm_h

///C(++) standard library header files:
#include <stdlib.h>///malloc(...)
#include <string.h>///strcpy(...)

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///TU_Bln361095CPUuse(IPv4or6fns),TU_Bln361095BSDsktUse(GetHostNm)
#include "errorCode.h"
///TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd,TU_Bln361095BSDsktDef
#include "socket.h"
#include <compiler/force_inline.h>///TU_Bln361095frcInln
#include <hardware/CPU/fastest_data_type.h>///TU_Bln361095CPUuse(FaststUint)
///TU_Bln361095MicroSoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

typedef /*char* int*/TU_Bln361095CPUuse(FaststUint) GetHostNmRtrnType;

#ifdef __cplusplus
  #define TU_Bln361095BSDsktGetHostNmRsltNmSpc\
    TU_Bln361095BSDsktNmSpc GetHostNm ::
/**Should be inside namespace TU_Bln361095BSDsktGetHostNmRsltNmSpc when macro
 * is expanded.*/
  #define TU_Bln361095BSDsktGetHostNmRsltDef(suffix) suffix
  #define TU_Bln361095BSDsktGetHostNmRsltUse(suffix)\
    TU_Bln361095BSDsktNmSpc GetHostNm :: suffix
#else///#ifdef __cplusplus
  #define TU_Bln361095BSDsktGetHostNmRsltDef(suffix)\
    TU_Bln361095BSDsktDef(GetHostNm##suffix)
  #define TU_Bln361095BSDsktGetHostNmRsltUse(suffix)\
    TU_Bln361095BSDsktUse(GetHostNm##suffix)
#endif///#ifdef __cplusplus
#if TU_Bln361095MicroSoftWindows
  #define TU_Bln361095BSDsktErrorNm(suffix) WSA##suffix
#else
  #define TU_Bln361095BSDsktErrorNm(suffix) suffix
#endif

#ifdef __cplusplus
namespace GetHostNm{
#endif

enum TU_Bln361095BSDsktDef(getHostNmRslt){
  TU_Bln361095BSDsktGetHostNmRsltDef(Success) = 0,
  TU_Bln361095BSDsktGetHostNmRsltDef(NoHostEntry),
  TU_Bln361095BSDsktGetHostNmRsltDef(NoIPaddr),
  TU_Bln361095BSDsktGetHostNmRsltDef(AllocMemFailed),
  TU_Bln361095BSDsktGetHostNmRsltDef(ArrTooLittle)};

#ifdef __cplusplus
}///End GetHostNm namespace
#endif

/**MinGW (at least 32 bit/older versions) does not have "getnameinfo". Use
 * "gethostbyaddr" then. You may also see "getnameinfo.h" in directory
 * "OperatingSystem/BSD/socket" of Stefan Gebauer's (TU Berlin matriculation
 * number 361095) "common_sourcecode" repository for availability of
 * "getnameinfo(...)"*/
#if defined TU_Bln361095IPv4 || defined TU_Bln361095autoIPv

///Stefan Gebauer's(TU Berlin mat.#361095)"common_sourcecode" repository files:
#include "sockaddr_in.h"///struct sockaddr_in
#include "gethostbyaddr.h"///gethostbyaddr(...)

TU_Bln361095BSDsktNmSpcBgn

#define functionAlreadyDefined

/**@brief This function is for Internet Protocol version (IPv)4 (only):"The addr
 *  argument of gethostbyaddr() shall be an in_addr structure when type is
 *  AF_INET." Use it if the version with getnameinfo(...) is not possible.:
 *  http://pubs.opengroup.org/onlinepubs/009696799/functions/gethostbyaddr.html
 * @param p_arHostName address where the address of an array or pointer is
 *   stored
 *  -Pass a stack-based character array as follows:
 *   "char arHostName[NI_MAXHOST];
 *   char * p_hostName = arHostName;
 *   TU_Bln361095BSDsktIPv4or6Use([...]&p_hostName[...]);"
 *   The pointer in this funtion is dereferenced twice, but the address of an
 *   array ("& arHostName") is the same as the address of its 1st character (
 *   "arHostName"==&arHostName[0]). So derefencing twice would take the value of
 *   the 1st character. This is why the additional pointer "p_hostName" is
 *   needed by the caller.
 *  -If you want to let allocatethe array on the heap by this function, do this:
 *   "char * p_hostName = NULL;
 *   TU_Bln361095BSDsktIPv4or6Use([...]&p_hostName[...]);"
 *   free() after use if the caller passed NULL to dereferenced parameter _and_
 *   the array was allocated )that means non-NULL after call to this function.
 * @return 0: success, else "h_errno" under Linux, WSAGetLastError()
 *  under Microsoft Windows*/
TU_Bln361095frcInln GetHostNmRtrnType TU_Bln361095BSDsktIPv4Def(GetHostName)(
  const struct sockaddr_in * const p_sockAddr_in,
  char ** p_arHostName,
  TU_Bln361095CPUuse(FaststUint) numChars,
  unsigned * p_rsltType
  )
{
///www.gnu.org/software/libc/manual/html_node/Host-Names.html
/** http://pubs.opengroup.org/onlinepubs/009696799/functions/gethostbyaddr.html
 *  :"Upon successful completion, these functions shall return a pointer to a
 *  hostent structure if the requested entry was found, and a null pointer if
 *  the end of the database was reached or the requested entry was not found."*/
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-gethostbyaddr
 * :"If no error occurs, gethostbyaddr returns a pointer to the hostent
 * structure. Otherwise, it returns a null pointer, and a specific error code
 * can be retrieved by calling WSAGetLastError."*/
  struct hostent * p_hostEntry =
///http://en.wikipedia.org/wiki/Berkeley_sockets#gethostbyname_and_gethostbyaddr
///http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-gethostbyaddr
    gethostbyaddr(
/** http://pubs.opengroup.org/onlinepubs/009696799/functions/gethostbyaddr.html
 *  :"The addr argument of gethostbyaddr() shall be an in_addr structure when
 *  type is AF_INET."*/
    (const char *) & p_sockAddr_in->sin_addr,///const void *addr,
    sizeof(p_sockAddr_in->sin_addr),///socklen_t len
    AF_INET///int type
    );
  if(p_hostEntry == NULL){//return h_errno if NULL?
//    return (GetHostNmRtrnType)TU_Bln361095BSDsktGetHostNmRsltUse(NoHostEntry);
    *p_rsltType = TU_Bln361095BSDsktUse(_h_errno);
    return TU_Bln361095BSDsktUse(GetLastHostError)();
  }
  const int numHostEntNmChrs = strlen(p_hostEntry->h_name);
  if(numChars < numHostEntNmChrs){
    *p_rsltType = TU_Bln361095BSDsktUse(GetHostNm);
     return (GetHostNmRtrnType)TU_Bln361095BSDsktGetHostNmRsltUse(ArrTooLittle);
  }
  if(*p_arHostName == NULL){
    numChars = numHostEntNmChrs + /**Terminating \0 character */1;
    *p_arHostName = (char *) malloc(numChars);
  }
  if(p_arHostName == NULL){///malloc(...) failed
    *p_rsltType = TU_Bln361095BSDsktUse(GetHostNm);
    return (GetHostNmRtrnType)TU_Bln361095BSDsktGetHostNmRsltUse(AllocMemFailed
      );
  }
  strcpy(*p_arHostName, p_hostEntry->h_name);
//  return p_arHostName;
  *p_rsltType = TU_Bln361095BSDsktUse(GetHostNm);
  return TU_Bln361095BSDsktGetHostNmRsltUse(Success);
}
TU_Bln361095BSDsktNmSpcEnd
#endif///#if defined TU_Bln361095IPv4 || defined TU_Bln361095autoIPv

#if defined(TU_Bln361095IPv4or6) || defined(TU_Bln361095autoIPv)

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///getnameinfo(...),getnameinfoNotDecl,getnameinfoInclInfo
#include "getnameinfo.h"

TU_Bln361095BSDsktNmSpcBgn

#ifdef getnameinfoNotDecl
  getnameinfoInclInfo
#else

/**@brief This function gets the host name for Internet Protocol version (IPv)4
 *  and 6:
 * http://pubs.opengroup.org/onlinepubs/009604599/functions/getnameinfo.html
 * @param p_arHostName address where the address of an array or pointer is stored
 *  -Pass a stack-based character array as follows:
 *   "char arHostName[NI_MAXHOST];
 *   char * p_hostName = arHostName;
 *   TU_Bln361095BSDsktIPv4or6Use([...]&p_hostName[...]);"
 *   The pointer in this funtion is dereferenced twice, but the address of an
 *   array ("& arHostName") is the same as the address of its 1st character (
 *   "arHostName"==&arHostName[0]). So derefencing twice would take the value of
 *   the 1st character. This is why the additional pointer "p_hostName" is
 *   needed by the caller.
 *  -If you want to let allocatethe array on the heap by this function, do this:
 *   "char * p_hostName = NULL;
 *   TU_Bln361095BSDsktIPv4or6Use([...]&p_hostName[...]);"
 *   free() after use if the caller passed NULL to dereferenced parameter _and_
 *   the array was allocated )that means non-NULL after call to this function.
 * @param numHostNmChars use an array of size NI_MAXHOST to be on the safe side
 * @return 0: success, else error code that can be used for gai_strerror() to
 *   get an error message for the error code.
 *  Microsoft Windows: caller can call function " WSAGetLastError" when this
 *   function returns non-0. So error messages can be printed in different
 *   languages via FormatMessage(...) */
TU_Bln361095frcInln GetHostNmRtrnType TU_Bln361095BSDsktIPv4or6Def(GetHostName)(
  struct addrinfo ** p_addrInfo,
//  char * arHostName,
  char ** p_arHostName,
  TU_Bln361095CPUuse(FaststUint) numHostNmChars,
  unsigned * p_rsltType)
{
  ///https://en.wikipedia.org/wiki/Getaddrinfo
  if(*p_arHostName == NULL){
    *p_arHostName = (char *) malloc(NI_MAXHOST);
    numHostNmChars = NI_MAXHOST;
  }
  if(p_arHostName == NULL){
    * p_rsltType = TU_Bln361095BSDsktUse(GetHostNm);
   return (GetHostNmRtrnType)TU_Bln361095BSDsktGetHostNmRsltUse(AllocMemFailed);
  }
/** http://pubs.opengroup.org/onlinepubs/009604599/functions/getnameinfo.html :
 * "A zero return value for getnameinfo() indicates successful completion" */
  const int getnameinfoRslt =
  /** http://man7.org/linux/man-pages/man3/getnameinfo.3.html :
   * "it converts a socket address to a corresponding host and service" */
//  http://de.wikipedia.org/wiki/Name_service_caching_daemon
    getnameinfo(
/** http://pubs.opengroup.org/onlinepubs/009604599/functions/getnameinfo.html :
 *  "const struct sockaddr *restrict sa"*/
     (**p_addrInfo).ai_addr, (*p_addrInfo)->ai_addrlen,
/** http://pubs.opengroup.org/onlinepubs/009604599/functions/getnameinfo.html :
 * "If the node argument is non-NULL and the nodelen argument is non-zero, then
 * the node argument points to a buffer able to contain up to nodelen characters
 * that receives the node name as a null-terminated string."*/
     *p_arHostName, /**nodelen*/numHostNmChars, NULL/**service*/,
     0/**service length*/,
/** http://pubs.opengroup.org/onlinepubs/009604599/functions/getnameinfo.html :
 * "If the flag bit NI_NAMEREQD is set, an error shall be returned if the host's
 * name cannot be located."*/NI_NAMEREQD/**flags*/);
//  if(getnameinfoRslt == 0)
//    return arHostName;
//  return (GetHostNmRtrnType)(getnameinfoRslt*/**Error codes are negative*/-1);
  * p_rsltType = TU_Bln361095BSDsktUse(IPv4or6fns);
  return getnameinfoRslt;
}
#endif///"#else" branch of #ifdef getnameinfoNotDecl
TU_Bln361095BSDsktNmSpcEnd
#endif///#if defined(TU_Bln361095IPv4or6) || defined(TU_Bln361095autoIPv)

#endif///#ifndef TU_Bln361095cmnSrcBSDsktGetHostNm_h