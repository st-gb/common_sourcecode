///(c)from 2020:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
///Created ca.01May2020 by Stefan Gebauer(TU Berlin matriculation number 361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Bln=BerLiN
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/Guard*/
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#else
///Include guard supported by (nearly) all industry compilers:
  #ifndef TU_Bln361095cmnSrcBSDskt_sktTimeOut_h
  #define TU_Bln361095cmnSrcBSDskt_sktTimeOut_h
#endif

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include "socket.h"///TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd

///Forward declarations:
struct timeval;

TU_Bln361095BSDsktNmSpcBgn

enum GetSocketTimeoutRslt{success, getRcvTimeoutError, getSndTimeoutError,
  getRcvAndSndTimeoutError};

///Use pointer ("*") rather than reference ("&") to avoid to enable C usage.
int getSocketTimeout(const int socketFileDesc, 
  struct timeval * timevalSocketTimeout, const int optName);
int setSocketTimeout(const int socketFileDesc, 
  struct timeval * p_timevalSocketTimeout, const int optName);
GetSocketTimeoutRslt GetSocketTimeoutInS(const int socketFileDesc, double * s);

TU_Bln361095BSDsktNmSpcEnd

#ifndef TU_Bln361095usePrgmInclGrd
#endif///#ifndef TU_Bln361095cmnSrcBSDskt_sktTimeOut_h
#endif