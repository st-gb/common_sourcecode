///(c)from 2021:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
///Created ca.13Apr2021 by Stefan Gebauer(TU Berlin matriculation number 361095)

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
  #ifndef TU_Bln361095POSIX_BSDskt_setBlockngMode_h
  #define TU_Bln361095POSIX_BSDskt_setBlockngMode_h
#endif

/// http://pubs.opengroup.org/onlinepubs/000095399/basedefs/fcntl.h.html
#include <fcntl.h>///fcntl(...),F_GETFL,F_SETFL,O_NONBLOCK

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///TU_Bln361095BSDsktNmSpcBgn,///TU_Bln361095BSDsktNmSpcEnd
#include <OperatingSystem/BSD/socket/socket.h>

TU_Bln361095BSDsktNmSpcBgn

/**@brief Sets the socket to non-blocking mode
 * @param sktFileDesc socket file descriptor. Should have been openend via
 *  "socket(...)" function before.*/
inline void setNonBlckng(const int sktFileDesc){
  ///see https://www.cs.odu.edu/~cs779/spring10/lectures/nonblockingIO.html
  int flags = fcntl(sktFileDesc, F_GETFL, 0);
  fcntl(sktFileDesc, F_SETFL, flags | O_NONBLOCK);
}

/**@brief Sets the socket to blocking mode
 * @param sktFileDesc socket file descriptor. Should have been openend via
 *  "socket(...)" function before.*/
inline void setBlockng(const int sktFileDesc){
  ///see https://www.cs.odu.edu/~cs779/spring10/lectures/nonblockingIO.html
  int flags = fcntl(sktFileDesc, F_GETFL, 0);
  fcntl(sktFileDesc, F_SETFL, flags &
    /** "~": invert every bit */(~ O_NONBLOCK) );
}

TU_Bln361095BSDsktNmSpcEnd

#ifndef TU_Bln361095usePrgmInclGrd
#endif///#ifndef TU_Bln361095POSIX_BSDskt_setBlockngMode_h
#endif