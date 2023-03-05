/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

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
 ! defined TU_Bln361095cmnSrc_hardware_dataCarrier_SMART_SMART_ID_prefix_h
   #define TU_Bln361095cmnSrc_hardware_dataCarrier_SMART_SMART_ID_prefix_h

/**TU_Bln361095hardwareDataCarrierNmSpc,
 * TU_Bln361095hardwareDataCarrierNmSpcBgn
 * TU_Bln361095hardwareDataCarrierNmSpcEnd */
#include <hardware/dataCarrier/dataCarrier_ID_prefix.h>

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095hardwareDataCarrierSMART_Def(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095hardwareDataCarrierSMART_NmSpc\
    TU_Bln361095hardwareDataCarrierNmSpc :: SMART
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierSMART_NmSpcBgn\
    TU_Bln361095hardwareDataCarrierNmSpcBgn namespace SMART{
  /**"}" times >>number of namespaces<<*/
  #define TU_Bln361095hardwareDataCarrierSMART_NmSpcEnd\
    TU_Bln361095hardwareDataCarrierNmSpcEnd }
  #define TU_Bln361095hardwareDataCarrierSMART_Use(suffix)\
    TU_Bln361095hardwareDataCarrierSMART_NmSpc :: suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095hardwareDataCarrierSMART_Def(suffix)\
    TU_Bln361095hardwareDataCarrierSMART_ ## suffix
/**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095hardwareDataCarrierSMART_NmSpc /** ->empty */
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierSMART_NmSpcBgn /** ->empty */
  #define TU_Bln361095hardwareDataCarrierSMART_NmSpcEnd /** ->empty */
  #define TU_Bln361095hardwareDataCarrierSMART_Use(suffix)\
    TU_Bln361095hardwareDataCarrierSMART_Def(suffix)
#endif

#endif///Include guard