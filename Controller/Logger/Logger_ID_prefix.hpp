/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * File name should contain "FileSys" to easier chose the correct file if
 * multiple "[...]ID_prefix.h" files are opened in an application. */

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
 ! defined TU_Bln361095cmnSrc__Logger__Logger_ID_prefix_h
   #define TU_Bln361095cmnSrc__Logger__Logger_ID_prefix_h

///TU_Bln361095cmnSrcNmSpc,TU_Bln361095cmnSrcNmSpcBgn,TU_Bln361095cmnSrcNmSpcEnd
#include <ID_prefix.h>

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095LoggerDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]FileSysNmSpc" */
  #define TU_Bln361095LoggerNmSpc TU_Bln361095nmSpc :: Logger
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095LoggerNmSpcBgn TU_Bln361095nmSpcBgn\
    namespace Logger{
  /**"}" times >>number of namespaces<<*/
  #define TU_Bln361095LoggerNmSpcEnd TU_Bln361095nmSpcEnd }
  #define TU_Bln361095LoggerUse(suffix) TU_Bln361095LoggerNmSpc ::\
    suffix
#endif

#endif///Include guard
