/**(c) from 2022 Stefan Gebauer, Computer Science Master(TU Berlin,matr.#361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * File name comes from:
 * ID=identifier:http://www.abbreviations.com/abbreviation/identifier
 * http://en.wikipedia.org/wiki/Identifier_(computer_languages) */

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
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[---]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095cmnSrcOpSysDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space*/
  #define TU_Bln361095cmnSrcOpSysNmSpc TU_Bln361095cmnSrcNmSpc :: OpSys ::
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcOpSysNmSpcBgn TU_Bln361095cmnSrcNmSpcBgn\
   namespace OpSys{
  #define TU_Bln361095cmnSrcOpSysNmSpcEnd TU_Bln361095cmnSrcNmSpcEnd }/**/
  #define TU_Bln361095cmnSrcOpSysUse(suffix) TU_Bln361095OpSysNmSpc suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095cmnSrcOpSysDef(suffix) TU_Bln361095cmnSrcOpSys##suffix
/**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095cmnSrcOpSysNmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcOpSysNmSpcBgn /** ->empty */
  #define TU_Bln361095cmnSrcOpSysNmSpcEnd /** ->empty */
  #define TU_Bln361095cmnSrcOpSysUse(suffix) TU_Bln361095cmnSrcOpSysDef(suffix)
#endif

#endif///Include guard
