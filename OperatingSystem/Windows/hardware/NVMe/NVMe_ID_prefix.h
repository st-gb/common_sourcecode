/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * Include "NVMe" into name of this file. So it is easer to choose the correct
 *  file if many "[...]ID_prefix.h" files are open in an application.*/

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
/**Bln=Berlin: http://www.acronymfinder.com/Berlin-(Bln).html 
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys */\
 ! defined TU_Bln361095OpSys_Windows_hardware_NVMe_NVMe_ID_prefix_h
   #define TU_Bln361095OpSys_Windows_hardware_NVMe_NVMe_ID_prefix_h

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
//#include "../hardware/OpSysWinHardware_ID_prefix.h"
/**Use Operating System-independent prefixes to enable cross-Operating System
 * support?!.*/
///TU_Bln361095hardwareDataCarrierNmSpcBgn
#include <hardware/dataCarrier/dataCarrier_ID_prefix.h>

#ifdef __cplusplus
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095hardwareDataCarrierNVMeDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095hardwareDataCarrierNVMeNmSpc\
    TU_Bln361095hardwareDataCarrierNmSpc :: NVMe
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierNVMeNmSpcBgn\
    TU_Bln361095hardwareDataCarrierNmSpcBgn namespace NVMe{
  #define TU_Bln361095hardwareDataCarrierNVMeNmSpcEnd\
    TU_Bln361095hardwareDataCarrierNmSpcEnd }
  #define TU_Bln361095hardwareDataCarrierNVMeUse(suffix)\
    TU_Bln361095hardwareDataCarrierNVMeNmSpc ## suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095hardwareDataCarrierNVMeDef(suffix) \
    TU_Bln361095hardwareDataCarrierNVMe##suffix
  #define TU_Bln361095hardwareDataCarrierNVMeUse(suffix) \
    TU_Bln361095hardwareDataCarrierNVMeDef(suffix)
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095hardwareDataCarrierNVMeNmSpc
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierNVMeNmSpcBgn
  #define TU_Bln361095hardwareDataCarrierNVMeNmSpcEnd
#endif

#endif///Include guard