/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * File name should contain "OpSysDataCarrier" to easier chose the correct file
 * if multiple "[...]ID_prefix.h" files are open in (the same) application(s).*/

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
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys
 * ID=IDentifier:http://www.abbreviations.com/abbreviation/identifier */\
 ! defined TU_Bln361095cmnSrc_OpSys_hardware_dataCarrier_OpSysDataCarrier_ID_prefix_h
   #define TU_Bln361095cmnSrc_OpSys_hardware_dataCarrier_OpSysDataCarrier_ID_prefix_h

///Stefan Gebauer's(TU Berlin matr.#361095)~"common_sourcecode"repository files:
 /**TU_Bln361095OpSysDef,TU_Bln361095OpSysNmSpc,TU_Bln361095OpSysNmSpcBgn,
  * TU_Bln361095OpSysNmSpcEnd */
#include <OperatingSystem/OpSys_ID_prefix.h>

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095OpSysDataCarrierDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]DataCarrierNmSpc" */
  #define TU_Bln361095OpSysDataCarrierNmSpc\
    TU_Bln361095OpSysNmSpc :: dataCarrier
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysDataCarrierNmSpcBgn\
    TU_Bln361095OpSysNmSpcBgn namespace dataCarrier{
  /**"}" times >>number of namespaces<<*/
  #define TU_Bln361095OpSysDataCarrierNmSpcEnd\
    TU_Bln361095OpSysNmSpcEnd }
  #define TU_Bln361095OpSysDataCarrierUse(suffix)\
    TU_Bln361095OpSysDataCarrierNmSpc :: suffix
#else
///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095OpSysDataCarrierDef(suffix) TU_Bln361095OpSysDef(\
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/\
    DataCarrier ## suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
///"C" language has no namespaces->Replace with empty character string.
  #define TU_Bln361095OpSysDataCarrierNmSpc /** ->empty */
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysDataCarrierNmSpcBgn /** ->empty */
  #define TU_Bln361095OpSysDataCarrierNmSpcEnd /** ->empty */
  #define TU_Bln361095OpSysDataCarrierUse(suffix)\
    TU_Bln361095OpSysDataCarrierDef(suffix)
#endif

#endif///include guard
