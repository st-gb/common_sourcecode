/**(c)2022 Stefan Gebauer,M.Sc.Comp.Sc.(TU Berlin matriculation number 361095)
 * File name comes from:
 * ID=identifier:http://www.abbreviations.com/abbreviation/identifier
 * http://en.wikipedia.org/wiki/Identifier_(computer_languages)*/
///Include guard,see http://en.wikipedia.org/wiki/Include_guard
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
 * http://www.abbreviations.com/abbreviation/Operating+System*/\
 ! defined TU_Bln361095cmnSrc_OpSys_ID_prefix_h
   #define TU_Bln361095cmnSrc_OpSys_ID_prefix_h

#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Definition should be in namespace via TU_Bln361095OpSysNmSpcBgn before.*/
 #define TU_Bln361095OpSysDef(suffix) suffix
/**Use these macros in source code to enable simple exchange.
 * Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space*/
 #define TU_Bln361095OpSysNmSpc TU_Bln361095 :: cmnSrc :: OpSys ::
 #define TU_Bln361095OpSysNmSpcBgn namespace TU_Bln361095{namespace cmnSrc{\
   namespace OpSys{
 #define TU_Bln361095OpSysNmSpcEnd }}}/**/
 #define TU_Bln361095OpSysUse(suffix) TU_Bln361095OpSysNmSpc suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
 #define TU_Bln361095OpSysDef(suffix) TU_Bln361095OpSys##suffix
/**"C" language has no namespaces->Replace with empty character string.*/
 #define TU_Bln361095OpSysNmSpc
 #define TU_Bln361095OpSysNmSpcBgn
 #define TU_Bln361095OpSysNmSpcEnd
 #define TU_Bln361095OpSysUse(suffix) TU_Bln361095OpSys##suffix
#endif

#endif///TU_Bln361095cmnSrc_OpSys_ID_prefix_h
