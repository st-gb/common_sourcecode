/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * Put file above "OperatingSystem" directory because it is related to it/uses
 * its functions. */

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys
 * Num=NUMber: http://www.abbreviations.com/abbreviation/number
 * B=Byte: http://www.abbreviations.com/abbreviation/byte
 * OS=Operating System: http://www.abbreviations.com/OS */\
 ! defined TU_Bln361095OpSys_hardware_dataCarrier_getNumBwrittenSinceOSstart_h
   #define TU_Bln361095OpSys_hardware_dataCarrier_getNumBwrittenSinceOSstart_h

///Stefan Gebauer's(TU Berlin matr.#361095)~"common_sourcecode"repository files:
 /**TU_Bln361095OpSysDataCarrierNmSpc, TU_Bln361095OpSysDataCarrierNmSpcBgn,
  * TU_Bln361095OpSysDataCarrierNmSpcEnd */
#include "OpSysDataCarrier_ID_prefix.h"
 ///TU_Bln361095MicroSoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartDef(suffix)\
    suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartNmSpc\
    TU_Bln361095OpSysDataCarrierNmSpc :: \
/**Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]GetNumWrittenBsinceOSstartNmSpc" */\
      getNumWrittenBsinceOSstart
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartNmSpcBgn\
    TU_Bln361095OpSysDataCarrierNmSpcBgn namespace getNumWrittenBsinceOSstart{
  #define TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartNmSpcEnd\
    TU_Bln361095OpSysDataCarrierNmSpcEnd }  
  #define TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartUse(suffix)\
    TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartNmSpc :: suffix
#else
///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartDef(suffix)\
    TU_Bln361095OpSysDataCarrierDef(\
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/\
      GetNumWrittenBsinceOSstart ## suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
///"C" language has no namespaces->Replace with empty character string.
  #define TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartNmSpc
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartNmSpcBgn
  #define TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartNmSpcEnd
  #define TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartUse(suffix)\
    TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartDef(suffix)
#endif

TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartNmSpcBgn

enum TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartDef(Rslt) {
  TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartDef(Success) = 0,
  TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartDef(
    OpenDataCarrierFaild),///Faild=FAILeD
  TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartDef(Error)
};

TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartNmSpcEnd

#ifdef __linux__
  #include <OperatingSystem/Unix/hardware/dataCarrier/getNumBwrittenSinceOSstart.hpp>
#endif
#ifdef /*_WIN32*/TU_Bln361095MicroSoftWindows
  #include <OperatingSystem/Windows/hardware/dataCarrier/getNumBwrittenSinceOSstart.h>
#endif

#endif///include guard
