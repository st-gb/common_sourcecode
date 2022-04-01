#pragma once///Include guard,see http://en.wikipedia.org/wiki/Include_guard
///TU_Bln361095MicroSoftWindows
#include <OperatingSystem/Windows/MicroSoftWindows.h>

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
#define TU_Bln361095BSDsktNmSpcBgn /*namespace TU_Berlin361095{*/namespace\
 OperatingSystem{namespace BSD{namespace sockets{
#define TU_Bln361095BSDsktNmSpcEnd /*}*/}}}

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif
enum errorCodes{connRefused, inProgress, timedOut,
 /** As return value if no other value fits. */ other};
#ifdef __cplusplus
}}}
#endif
#define TU_Bln361095BSDsktUse(suffix) TU_Bln361095BSDsktNmSpc suffix
/**Def=definition: http://www.abbreviations.com/abbreviation/definition 
 * Definition should be in namespace via TU_Bln361095BSDsktNmSpcBgn before.*/
#define TU_Bln361095BSDsktDef(suffix) suffix

#else///#ifdef __cplusplus
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation : "The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
/**"C" language has no namespaces->Replace with empty character string.*/
#define TU_Bln361095BSDsktNmSpc 
#define TU_Bln361095BSDsktNmSpcBgn
#define TU_Bln361095BSDsktNmSpcEnd
#define TU_Bln361095BSDsktDef(suffix) TU_Bln361095BSDsktPrfx(suffix)
#define TU_Bln361095BSDsktUse(suffix) TU_Bln361095BSDsktPrfx(suffix)
#endif///#ifdef __cplusplus
#ifdef __linux__
  #include <OperatingSystem/POSIX/BSD_sockets/sockets.h>
#endif
#ifdef TU_Bln361095MicroSoftWindows
  #include <OperatingSystem/Windows/BSD_sockets/sockets.h>///InitSocket(...)
#endif

