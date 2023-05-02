/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * Include "dataCarrier" into name of this file. So it is easer to choose the
 * correct file if many "[...]ID_prefix.h" files are open in an application.*/

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
/**Bln=Berlin:http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * ID=identifier:http://www.abbreviations.com/abbreviation/identifier */\
 ! defined TU_Bln361095cmnSrc_hardware_dataCarrier_dataCarrier_ID_prefix_h
   #define TU_Bln361095cmnSrc_hardware_dataCarrier_dataCarrier_ID_prefix_h

/**TU_Bln361095hardwareNmSpc,
 * TU_Bln361095hardwareNmSpcBgn
 * TU_Bln361095hardwareNmSpcEnd */
#include <hardware/hardware_ID_prefix.h>

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095hardwareDataCarrierDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095hardwareDataCarrierNmSpc\
/**Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]DataCarrierNmSpc" */\
    TU_Bln361095hardwareNmSpc :: dataCarrier
  ///Shorter than with including "hardware"
  #define TU_Bln361095dataCarrierNmSpc\
/**Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]dataCarrierNmSpc" */\
    TU_Bln361095nmSpc :: dataCarrier
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierNmSpcBgn\
    TU_Bln361095hardwareNmSpcBgn namespace dataCarrier{
  ///Shorter than with including "hardware"
  #define TU_Bln361095dataCarrierNmSpcBgn\
    TU_Bln361095nmSpcBgn namespace dataCarrier{
  /**"}" times >>number of namespaces<<*/
  #define TU_Bln361095hardwareDataCarrierNmSpcEnd\
    TU_Bln361095hardwareNmSpcEnd }
  ///Shorter than with including "hardware"
  #define TU_Bln361095dataCarrierNmSpcEnd\
    TU_Bln361095nmSpcEnd }
  #define TU_Bln361095hardwareDataCarrierUse(suffix)\
    TU_Bln361095hardwareDataCarrierNmSpc :: suffix
  ///Shorter than with including "hardware"
  #define TU_Bln361095dataCarrierUse(suffix)\
    TU_Bln361095dataCarrierNmSpc :: suffix
#else
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095hardwareDataCarrierDef(suffix)\
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/\
    TU_Bln361095hardwareDataCarrier ## suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
/**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095hardwareDataCarrierNmSpc /** ->empty */
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierNmSpcBgn /** ->empty */
  #define TU_Bln361095hardwareDataCarrierNmSpcEnd /** ->empty */
  #define TU_Bln361095hardwareDataCarrierUse(suffix)\
    TU_Bln361095hardwareDataCarrierDef(suffix)
#endif

#endif///Include guard