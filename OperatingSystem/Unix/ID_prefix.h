///(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

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
 * OpSys=Operating System:
 *  http://www.abbreviations.com/abbreviation/Operating+System 
 * ID=Identifier:
 *  http://en.wikipedia.org/wiki/Identifier#In_computer_languages */\
 ! defined TU_Bln361095cmnSrc_OpSys_Unix_ID_prefix_h
   #define TU_Bln361095cmnSrc_OpSys_Unix_ID_prefix_h

#include "../ID_prefix.h"///TU_Bln361095OpSysDef(...)

/**Use these preprocessor macros in source code for example to enable both C and
 * C++. */
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095cmnSrcOpSysUnixDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space*/
  #define TU_Bln361095cmnSrcOpSysUnixNmSpc TU_Bln361095cmnSrcOpSysNmSpc :: Unix
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcOpSysUnixNmSpcBgn TU_Bln361095cmnSrcOpSysNmSpcBgn\
 namespace Unix{
  #define TU_Bln361095cmnSrcOpSysUnixNmSpcEnd TU_Bln361095cmnSrcOpSysNmSpcEnd }
  #define TU_Bln361095cmnSrcOpSysUnixUse(suffix)\
    TU_Bln361095cmnSrcOpSysUnixNmSpc :: suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095cmnSrcOpSysUnixDef(suffix)\
    TU_Bln361095cmnSrcOpSysDef(Unix##suffix)
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space
 * "C" language has no namespaces->Replace with empty character string. */
  #define TU_Bln361095cmnSrcOpSysUnixNmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcOpSysUnixNmSpcBgn /** ->empty */
  #define TU_Bln361095cmnSrcOpSysUnixNmSpcEnd /** ->empty */
  #define TU_Bln361095cmnSrcOpSysUnixUse(suffix)\
    TU_Bln361095cmnSrcOpSysUnixDef(suffix)
#endif

#endif///Include guard
