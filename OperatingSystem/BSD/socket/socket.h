///(c)from 2020 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
#ifdef TU_Berlin361095usePrgmInclGrd
  #pragma once
#if ! defined TU_Berlin361095usePrgmInclGrd && \
  /**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Berlin361095cmnSrcBSDskt_socket_h
  #define TU_Berlin361095cmnSrcBSDskt_socket_h

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///TU_Bln361095MicroSoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

/* Include this file in order to get OS-independent the socket(...)
 * declaration.*/

#ifdef __cplusplus

/**Bln=Berlin
 * skt=socket: http://www.allacronyms.com/socket/abbreviated
 * Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space*/
#define TU_Bln361095BSDsktNmSpc /*TU_Berlin361095::*/OperatingSystem::BSD::\
sockets::
/**Bgn=begin: http://www.allacronyms.com/begin/abbreviated */
///Use this macro in source code to enable namespace change at a central point.
#define TU_Bln361095BSDsktNmSpcBgn /*namespace TU_Berlin361095{*/namespace\
 OperatingSystem{namespace BSD{namespace sockets{
///Use this macro in source code to enable namespace change at a central point.
#define TU_Bln361095BSDsktNmSpcEnd /*}*/}}}

 #define TU_Bln361095BSDsktUse(suffix) TU_Bln361095BSDsktNmSpc suffix
/**Def=definition: http://www.abbreviations.com/abbreviation/definition 
 * Definition should be in namespace via TU_Bln361095BSDsktNmSpcBgn before.*/
 #define TU_Bln361095BSDsktDef(suffix) suffix
 ///Don't need to add "IPv4" because C++ can do function overloading.
 #define TU_Bln361095BSDsktIPv4Def(suffix) TU_Bln361095BSDsktDef(suffix)
 #define TU_Bln361095BSDsktIPv4Use(suffix) TU_Bln361095BSDsktUse(suffix)
 ///Don't need to add "IPv4or6" because C++ can do function overloading.
 #define TU_Bln361095BSDsktIPv4or6Def(suffix)\
  TU_Bln361095BSDsktPrfx(suffix)

#else///#ifdef __cplusplus
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation : "The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///"TU_Berlin" is the shortest unambiguous token.(Bln=Berlin only in German?)
/**Prefix with TU_Bln361095 to avoid name clashes (e.g. with external headers)
 * Enclosed names should begin with capital letters for better readability.*/
#define TU_Bln361095BSDsktPrfx(suffix) TU_Bln361095BSDskt##suffix
/**"C" language has no namespaces->Replace with empty character string.*/
#define TU_Bln361095BSDsktNmSpc 
#define TU_Bln361095BSDsktNmSpcBgn
#define TU_Bln361095BSDsktNmSpcEnd
 #define TU_Bln361095BSDsktDef(suffix) TU_Bln361095BSDsktPrfx(suffix)
 #define TU_Bln361095BSDsktIPv4Def(suffix) TU_Bln361095BSDsktPrfx(IPv4##suffix)
 /**The "use" functions are set up after the IP version type is known (if
  * automatic IP version). This is done in file system file "sktAddrType.h".*/
 #define TU_Bln361095BSDsktIPv4or6Def(suffix)\
  TU_Bln361095BSDsktPrfx(IPv4or6##suffix)
 ///If not 2 version/not differentiated between IP version 4 or 4 and 6
 #define TU_Bln361095BSDsktUse(suffix) TU_Bln361095BSDsktPrfx(suffix)
#endif///#ifdef __cplusplus
#ifdef __linux__
  #include <OperatingSystem/POSIX/BSD_sockets/sockets.h>
#endif
#ifdef TU_Bln361095MicroSoftWindows
  #include <OperatingSystem/Windows/BSD_sockets/sockets.h>///InitSocket(...)
#endif

#endif///TU_Berlin361095cmnSrcBSDskt_socket_h
