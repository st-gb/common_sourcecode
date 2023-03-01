///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard

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
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put Definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095cmnSrcCstdLibDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095cmnSrcCstdLibNmSpc TU_Bln361095cmnSrcNmSpc :: CstdLib
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcCstdLibNmSpcBgn TU_Bln361095cmnSrcNmSpcBgn\
    namespace CstdLib{
  #define TU_Bln361095cmnSrcCstdLibNmSpcEnd TU_Bln361095cmnSrcNmSpcEnd }
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095cmnSrcCstdLibDef(suffix) TU_Bln361095cmnSrcCstdLib##suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space
 * "C" language has no namespaces->Replace with empty character string. */
  #define TU_Bln361095cmnSrcCstdLibNmSpc /**->empty*/
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcCstdLibNmSpcBgn /**->empty*/
  #define TU_Bln361095cmnSrcCstdLibNmSpcEnd /**->empty*/
  #define TU_Bln361095cmnSrcCstdLibUse(suffix)\
    TU_Bln361095cmnSrcCstdLibDef(suffix)
#endif

#endif///Include guard
