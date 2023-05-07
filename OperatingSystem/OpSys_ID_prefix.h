/**(c) from 2022 Stefan Gebauer, Computer Science Master(TU Berlin,matr.#361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * File name should contain "OpSys" to easier chose the correct file if multiple
 * "[...]ID_prefix.h" files are opened in an application.
 * File name comes from:
 *  OpSys=Operating System:
 *   http://www.abbreviations.com/abbreviation/Operating+System
 *  ID=identifier:http://www.abbreviations.com/abbreviation/identifier
 *   http://en.wikipedia.org/wiki/Identifier_(computer_languages) */

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
/**Bln=Berlin:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=common:http://www.abbreviations.com/abbreviation/common
 * Src=source:http://www.abbreviations.com/abbreviation/Source
 * OpSys=Operating System:
 *  http://www.abbreviations.com/abbreviation/Operating+System
 * ID=identifier:http://www.abbreviations.com/abbreviation/identifier */\
 ! defined TU_Bln361095cmnSrc_OpSys_ID_prefix_h
   #define TU_Bln361095cmnSrc_OpSys_ID_prefix_h

///TU_Bln361095cmnSrcNmSpc,TU_Bln361095cmnSrcNmSpcBgn,TU_Bln361095cmnSrcNmSpcEnd
#include "../ID_prefix.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++. */
#ifdef __cplusplus
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095OpSysDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" to the namespace to enable "using namespace [...]NmSpc */
  #define TU_Bln361095OpSysNmSpc TU_Bln361095nmSpc :: OpSys
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysNmSpcBgn TU_Bln361095nmSpcBgn\
   namespace OpSys{
  #define TU_Bln361095OpSysNmSpcEnd TU_Bln361095nmSpcEnd }
  #define TU_Bln361095OpSysUse(suffix) TU_Bln361095OpSysNmSpc ::\
    suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095OpSysDef(suffix) TU_Bln361095def(OpSys##suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
/**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095OpSysNmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysNmSpcBgn /** ->empty */
  #define TU_Bln361095OpSysNmSpcEnd /** ->empty */
  #define TU_Bln361095OpSysUse(suffix) TU_Bln361095OpSysDef(suffix)
#endif

#endif///Include guard
