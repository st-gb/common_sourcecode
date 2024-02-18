/**File name "[...]IDprfx" comes from:
 * -ID=IDentifier : http://www.abbreviations.com/abbreviation/identifier
 * -prfx=PReFiX : http://www.abbreviations.com/abbreviation/Prefix
 * (c)from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
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
 ! defined TU_Bln361095cmnSrc__compiler__compilerIDprfx_h
   #define TU_Bln361095cmnSrc__compiler__compilerIDprfx_h

#include <ID_prefix.h>///TU_Bln361095

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]nmSpcBgn" and "[...]nmSpcEnd" #define'd below.*/
  #define TU_Bln361095compilerDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095compilerNmSpc\
/**Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]compilerNmSpc" */\
    TU_Bln361095nmSpc :: compiler
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095compilerNmSpcBgn\
    TU_Bln361095nmSpcBgn namespace compiler{
  #define TU_Bln361095compilerNmSpcEnd TU_Bln361095nmSpcEnd }
  #define TU_Bln361095compilerUse(suffix) TU_Bln361095compilerNmSpc :: suffix
#else///C compiler
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095compilerDef(suffix)\
    TU_Bln361095def(compiler##suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * "C" language has no namespaces->Replace with empty character string. */
  #define TU_Bln361095compilerNmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095compilerNmSpcBgn /** ->empty */
  #define TU_Bln361095compilerNmSpcEnd /** ->empty */
  #define TU_Bln361095compilerUse(suffix)\
    TU_Bln361095compilerDef(suffix)
#endif

#endif///Include guard
