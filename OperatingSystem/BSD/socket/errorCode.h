///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcBSDskt_errorCode_h
#define TU_Bln361095cmnSrcBSDskt_errorCode_h

TU_Bln361095BSDsktNmSpcBgn

enum TU_Bln361095BSDsktDef(RsltType){
/**Error code type of older BSD sockets function. For example see
 * http://en.wikipedia.org/wiki/Berkeley_sockets#gethostbyname_and_gethostbyaddr
 */
  TU_Bln361095BSDsktDef(_h_errno),
/**Newer Internet Procotol version 6-capable (POSIX) functions like
 * getnameinfo(...). Error codes of this type can be passed to function
 * "gai_strerror"(...) to get error messages for the code.*/
  TU_Bln361095BSDsktDef(IPv4or6fns),
///Error code specific to "TU_Bln361095BSDsktUse(GetHostName)" function.
  TU_Bln361095BSDsktDef(GetHostNm)};

#ifdef __linux__
  #include <OperatingSystem/POSIX/BSD_sockets/errorCode.h>
#endif

/**Force inlining to avoid multiple definitions of this function when linking->
 * compiler error.*/
/**@param rslt result value of type @param rsltType
 * @param rsltType type of the result value, for example "h_errno" errors
 * @return (English) error message or NULL if @param rsltType is not supported*/
TU_Bln361095frcInln const char * TU_Bln361095BSDsktDef(GetErrorMsg)(
  const int rslt,
  const unsigned rsltType)
{
  switch((enum TU_Bln361095BSDsktUse(RsltType) ) rsltType){
    case TU_Bln361095BSDsktUse(IPv4or6fns): return gai_strerror(rslt);
    case TU_Bln361095BSDsktUse(_h_errno): return hstrerror(rslt);
  }
  return NULL;
}

TU_Bln361095BSDsktNmSpcEnd

#endif///#ifndef TU_Bln361095cmnSrcBSDskt_errorCode_h
