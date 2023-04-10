///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
/**File name should contain "CPU" to make it easier to chose the correct file:
 * when multiple "[...]ID_prefix.h" are open in the same application.
 * @author Stefan Gebauer (TU Berlin matriculation number 361095)
 * Created on 23. April 2022, 22:16 */

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
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 * ID=IDentifier: http://www.abbreviations.com/abbreviation/identifier */\
 ! defined TU_Bln361095cmnSrc_hardware_CPU_hardwareCPU_ID_prefix_h
   #define TU_Bln361095cmnSrc_hardware_CPU_hardwareCPU_ID_prefix_h

/**TU_Bln361095hardwareNmSpc,TU_Bln361095hardwareNmSpcBgn,
 * TU_Bln361095hardwareNmSpcEnd*/
#include "../hardware_ID_prefix.h"

/**Use the following preprocessor macros in source code for example to enable
 * both C and C++.*/
#ifdef __cplusplus
/**The following prefixes are shorter than the more precisely scoped
 * "hardwareCPU" or "cmnSrcHardwareCPU". They are provided for convenience
 * (less typing) to use the datatype "FastUint" that may be often used in
 * source code, for example in "for"-loops.*/
/**def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095CPUdef(suffix) suffix
/**nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]CPUnmSpc".*/
  #define TU_Bln361095CPUnmSpc TU_Bln361095nmSpc :: CPU
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095CPUnmSpcBgn TU_Bln361095nmSpcBgn namespace CPU{
  #define TU_Bln361095CPUnmSpcEnd TU_Bln361095nmSpcEnd }
  #define TU_Bln361095CPUuse(suffix) TU_Bln361095CPUnmSpc :: suffix

/**def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095hardwareCPUdef(suffix) suffix
/**nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]CPUnmSpc".*/
  #define TU_Bln361095hardwareCPUnmSpc TU_Bln361095hardwareNmSpc :: CPU
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareCPUnmSpcBgn TU_Bln361095hardwareNmSpcBgn\
   namespace CPU{
  #define TU_Bln361095hardwareCPUnmSpcEnd TU_Bln361095hardwareNmSpcEnd }
  #define TU_Bln361095hardwareCPUuse(suffix)\
    TU_Bln361095hardwareCPUnmSpc :: suffix
#else
/**The following prefixes are shorter than the more precisely scoped
 * "hardwareCPU" or "cmnSrcHardwareCPU". They are provided for convenience
 * (less typing) to use the datatype "FastUint" that may be often used in
 * source code, for example in "for"-loops.*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095CPUdef(suffix) TU_Bln361095def(CPU##suffix)
/**nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
/**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095CPUnmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095CPUnmSpcBgn /** ->empty */
  #define TU_Bln361095CPUnmSpcEnd /** ->empty */
  #define TU_Bln361095CPUuse(suffix) TU_Bln361095CPUdef(suffix)

///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095hardwareCPUdef(suffix)\
    TU_Bln361095hardwareDef(CPU##suffix)
/**nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
/**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095hardwareCPUnmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareCPUnmSpcBgn /** ->empty */
  #define TU_Bln361095hardwareCPUnmSpcEnd /** ->empty */
  #define TU_Bln361095hardwareCPUuse(suffix) TU_Bln361095hardwareCPUdef(suffix)
#endif

#endif///include guard
