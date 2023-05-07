/**(c) from 2022 Stefan Gebauer, Computer Science Master(TU Berlin,matr.#361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * File name should contain "OpSysWindows" to easier chose the correct file if
 * multiple "[...]ID_prefix.h" files are opened in an application.
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
/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem:
 *  http://www.abbreviations.com/abbreviation/Operating+System
 * ID=identifier:http://www.abbreviations.com/abbreviation/identifier */\
 ! defined TU_Bln361095cmnSrc_OpSys_Windows_OpSysWindows_ID_prefix_h
   #define TU_Bln361095cmnSrc_OpSys_Windows_OpSysWindows_ID_prefix_h

/**TU_Bln361095OpSysNmSpc,TU_Bln361095OpSysNmSpcBgn,
 * TU_Bln361095OpSysNmSpcEnd */
#include "../OpSys_ID_prefix.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++. */
#ifdef __cplusplus
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095OpSysWindowsDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]WindowsNmSpc".*/
  #define TU_Bln361095OpSysWindowsNmSpc TU_Bln361095OpSysNmSpc :: Windows
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysWindowsNmSpcBgn TU_Bln361095OpSysNmSpcBgn\
    namespace Windows{
  #define TU_Bln361095OpSysWindowsNmSpcEnd TU_Bln361095OpSysNmSpcEnd }
  #define TU_Bln361095OpSysWindowsUse(suffix)\
    TU_Bln361095OpSysWindowsNmSpc :: suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095OpSysWindowsDef(suffix)\
    TU_Bln361095OpSysDef(Windows##suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
/**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095OpSysWindowsNmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysWindowsNmSpcBgn /** ->empty */
  #define TU_Bln361095OpSysWindowsNmSpcEnd /** ->empty */
  #define TU_Bln361095OpSysWindowsUse(suffix)\
    TU_Bln361095OpSysWindowsDef(suffix)
#endif

#endif///Include guard