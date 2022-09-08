///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all compilers:
#ifndef TU_Bln361095cmnSrcBSDsktGetBinIPaddr_h
#define TU_Bln361095cmnSrcBSDsktGetBinIPaddr_h

///Stefan Gebauer's(TU Berlin mat#361095) "common_sourcecode" repository files:
/** preprocessor macros TU_Berlin361095BSDsktDef(...),
 *  TU_Berlin361095BSDscktsUse(...)*/
#include "socket.h"
///TU_Bln361095BSDsktUse(IPv4or6fns),TU_Bln361095BSDsktDef(_herrno)
#include "errorCode.h"
#include <hardware/CPU/fastest_data_type.h>///TU_Bln361095CPUuse(FaststUint)

TU_Bln361095BSDsktNmSpcBgn
#ifdef __cplusplus
 #define TU_Bln361095BSDsktGetBinIPaddrDef(suffix) \
  TU_Bln361095BSDsktDef(getBinIPaddr_##suffix)
 #define TU_Bln361095BSDsktGetBinIPaddrUse(suffix) \
  TU_Bln361095BSDsktUse(getBinIPaddr_##suffix)
#else
 #define TU_Bln361095BSDsktGetBinIPaddrDef(suffix) \
  TU_Bln361095BSDsktDef(getBinIPaddr_##suffix)
 #define TU_Bln361095BSDsktGetBinIPaddrUse(suffix) \
  TU_Bln361095BSDsktUse(getBinIPaddr_##suffix)
#endif

//enum TU_Berlin361095BSDscktsDef(getIPaddrRslt){success = 0}
enum TU_Bln361095BSDsktDef(getBinIPaddrRslt){
  TU_Bln361095BSDsktGetBinIPaddrDef(Success) = 0,
  TU_Bln361095BSDsktGetBinIPaddrDef(PrtCnvrtError),
  TU_Bln361095BSDsktGetBinIPaddrDef(UnsupportedProtoFam)
};
TU_Bln361095BSDsktNmSpcEnd

#if defined TU_Bln361095IPv4 || defined TU_Bln361095autoIPv

///C standard header files:
#include <string.h>///memset(...),memcpy(...)

///Stefan Gebauer's(TU Berlin mat#361095) "common_sourcecode" repository files:
#include "sockaddr_in.h"///struct sockaddr_in
#include "getHostDBentry.h"///BSDsocketsPrefix(GetHostDataBaseEntry)
#ifdef __cplusplus
#include <character_string/ConvertToTypename.hpp>///ConvertToTypename(...)
#endif

TU_Bln361095BSDsktNmSpcBgn

TU_Bln361095frcInln void hostentTo_sockaddr_in(
  const int portNumber,
  const struct hostent * const p_hostDataBaseEntry,
  struct sockaddr_in * const p_sockAddr//,
  )
{
  /** http://www.gnu.org/software/libc/manual/html_node/Host-Names.html :
   *  "int h_addrtype
   *  This is the host address type; in practice, its value is always either
   *  AF_INET or AF_INET6, with the latter being used for IPv6 hosts. In
   *  principle other kinds of addresses could be represented in the database as
   *  well as Internet addresses; if this were done, you might find a value in
   *  this field other than AF_INET or AF_INET6. See Socket Addresses." */
  if(p_hostDataBaseEntry->h_addrtype != AF_INET)
    return;//TU_Berlin361095BSDscktsGetIPaddrUse(UnsupportedProtoFam);
  p_sockAddr->sin_family = AF_INET;
  /** http://man7.org/linux/man-pages/man3/memset.3.html :
   * -"memset(void *s,  int c, size_t n);"
   * -Sets no error.*/
  memset(
  /** http://www.cs.cmu.edu/~srini/15-441/S10/lectures/r01-sockets.pdf :
   *  "memset(struct sockaddr_in,  '\0', sizeof(sockaddr_in));" */
    (void *) p_sockAddr, 0, sizeof(*p_sockAddr) );

  /** http://man7.org/linux/man-pages/man3/memcpy.3.html :
   * -"void *memcpy(void *restrict dest, const void *restrict src, size_t n);"
   * -Sets not Operating System error code and returns no error. */
  memcpy(
  //TODO cite sources for the following code:
  /** http://www.gta.ufrj.br/ensino/eel878/sockets/gethostbynameman.html :
   * struct hostent.h_addr casted to "*(struct in_addr*)" */
  /** http://www.cs.cmu.edu/~srini/15-441/S10/lectures/r01-sockets.pdf :
   *  struct sockaddr_in.sin_addr.s_addr as destination, hostent.h_addr_list[0]
   *  as source, hostent.h_length as # B */
    (char *) & p_sockAddr->sin_addr.s_addr,///struct in_addr	 sin_addr
    (char *) p_hostDataBaseEntry->h_addr,
    p_hostDataBaseEntry->h_length);
  /** http://www.cs.cmu.edu/~srini/15-441/S10/lectures/r01-sockets.pdf :
   *  struct sockaddr_in.sin_port = htons(port); */
  p_sockAddr->sin_port = htons(portNumber);
}

/** @brief get binary IP address from host/domain name as struct
 *  @param host : host name or dotted IPv4 address as character string to get IP
 *   address struct for:
 * http://man7.org/linux/man-pages/man3/gethostbyname.3.html
 * "Here name is either a hostname or an IPv4 address in standard dot notation"
 * @return TU_Bln361095BSDsktGetBinIPaddrUse(Success) on success */
TU_Bln361095frcInln int TU_Bln361095BSDsktIPv4Def(GetBinIPaddr)(
  const char hostStr[],
  const int portNumber,
  struct sockaddr_in * p_sockAddr,
  TU_Bln361095CPUuse(FaststUint) * p_rsltType
  )
{
  struct hostent * p_hostDataBaseEntry;
  /*enum TU_Bln361095BSDsktUse(gethostbynameRslt)*/ int gethostbynameRslt =
    TU_Bln361095BSDsktUse(GetHostDataBaseEntry)(
      hostStr,
      & p_hostDataBaseEntry);
  if( ! p_hostDataBaseEntry ){
//    stage_ = getHostDBentry;
    * p_rsltType = TU_Bln361095BSDsktUse(_h_errno);
    return /*getHostByNameFailed*/ /*getHostByNameFailed +*/ gethostbynameRslt;
  }
  /*return*/ hostentTo_sockaddr_in(
    portNumber,
    p_hostDataBaseEntry,
    p_sockAddr
    );
  return TU_Bln361095BSDsktGetBinIPaddrUse(Success);
}

///Only a 2nd function with the same name if function overloading is possible.
#ifdef __cplusplus
TU_Bln361095frcInln int TU_Bln361095BSDsktIPv4Def(GetBinIPaddr)(
  const char hostStr[],
  const char portStr[],
  struct sockaddr_in * p_sockAddr
  )
{
  //const int portNumber = atoi(portStr);
//  char * p_end;
//  long int portNumber = strtol(portStr,///const char* str,
//    & p_end,///char** endptr,
//    10///int base
//    );
//  if(portNumber == 0)
//    return 1;
  if(ConvertToTypename(
    portNumber,
    portStr)
    )
  return TU_Bln361095BSDsktIPv4Use(GetBinIPaddr)(
    hostStr,
    portNumber,
    p_sockAddr
    );
  return TU_Bln361095BSDsktIPv4Use(PrtCnvrtError);
}
#endif///#ifdef __cplusplus

TU_Bln361095BSDsktNmSpcEnd
#endif///IPv4 or autoIP

#if defined TU_Bln361095IPv4or6 || defined TU_Bln361095autoIPv
///http://en.wikipedia.org/wiki/Getaddrinfo
#include "addrinfo.h"///struct addrinfo
#include "getaddrinfo.h"///getaddrinfo(...), getaddrinfoMayBeDecl

TU_Bln361095BSDsktNmSpcBgn

#ifndef TU_Bln361095BSDskt_getaddrinfoNotDecl

//  #pragma message "TU_Bln361095BSDsktIPv4or6Def(GetIPaddr)"

/**@param host:host name or dotted IPv4/6 address as character string to get IP
 *  address struct for
 * @param portStr : port number or service name like "echo"
 *  http://en.wikipedia.org/wiki/Getaddrinfo :
 *  "In the latter case a typical implementation uses getservbyname() to query
 *  the file /etc/services to resolve the service to a port number."
 * @pp_sktAddr a list of (binary encoded) socket addresses filled by function
 *  getaddrinfo(...)
 * @return return value of POSIX/BSD function "getaddrinfo(...)". So a character
 *  string can be got for it via function "gai_strerror(...)"*/
TU_Bln361095frcInln int TU_Bln361095BSDsktIPv4or6Def(GetBinIPaddr)(
  const char hostStr[],
  const char portStr[],
  struct addrinfo ** pp_sktAddr,
  TU_Bln361095CPUuse(FaststUint) * p_rsltType
  )
{
  * p_rsltType = TU_Bln361095BSDsktUse(IPv4or6fns);
/** http://pubs.opengroup.org/onlinepubs/009619199/getad.htm :
 * "A zero return value for getaddrinfo() indicates successful completion; a
 *  non-zero return value indicates failure."*/
  return /**int*/
/**http://pubs.opengroup.org/onlinepubs/009619199/getad.htm :"[...]returns a set
 * of socket addresses and associated information"*/
  ///"getaddrinfo" is POSIX, not BSD?!
   getaddrinfo(
    hostStr,///const char* hostname,
    portStr,///const char* service,
    NULL,///const struct addrinfo* hints,
    pp_sktAddr///struct addrinfo** result
    );
}
#endif///#ifndef getaddrinfoMayBeDecl

TU_Bln361095BSDsktNmSpcEnd

#endif///IPv4,6 or autoIPv
#endif///#ifndef TU_Bln361095cmnSrcBSDsktGetBinIPaddr_h