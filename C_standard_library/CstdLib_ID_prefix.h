/**(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * File name should contain "CstdLib" to easier chose the correct file if
 * multiple "[...]ID_prefix.h" files are open in an application. */

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
/**cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * std=STandarD:http://www.abbreviations.com/abbreviation/standard
 * Lib=LIBrary http://www.abbreviations.com/abbreviation/Library
 * ID=Identifier:
 *  http://en.wikipedia.org/wiki/Identifier#In_computer_languages */\
 ! defined TU_Bln361095cmnSrcCstdLibIDprefx_h
   #define TU_Bln361095cmnSrcCstdLibIDprefx_h

///TU_Bln361095cmnSrcNmSpc,TU_Bln361095cmnSrcNmSpcBgn,TU_Bln361095cmnSrcNmSpcEnd
#include "../ID_prefix.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++. */
#ifdef __cplusplus
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put Definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095CstdLibDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]CstdLibNmSpc".*/
  #define TU_Bln361095CstdLibNmSpc TU_Bln361095nmSpc :: CstdLib
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095CstdLibNmSpcBgn TU_Bln361095nmSpcBgn\
    namespace CstdLib{
  #define TU_Bln361095CstdLibNmSpcEnd TU_Bln361095nmSpcEnd }
  #define TU_Bln361095CstdLibUse(suffix) TU_Bln361095CstdLibNmSpc :: suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095CstdLibDef(suffix) TU_Bln361095def(CstdLib##suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * "C" language has no namespaces->Replace with empty character string. */
  #define TU_Bln361095CstdLibNmSpc /**->empty*/
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095CstdLibNmSpcBgn /**->empty*/
  #define TU_Bln361095CstdLibNmSpcEnd /**->empty*/
  #define TU_Bln361095CstdLibUse(suffix)\
    TU_Bln361095CstdLibDef(suffix)
#endif

#endif///Include guard
