/**(c) Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * File name should contain "OpSysProcess" to easier chose the correct file
 * if multiple "[...]ID_prefix.h" files are opened in the same application.*/

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif

/**Include guard supported by (nearly) all industry compilers:*/
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Bln=Berlin:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem:http://www.abbreviations.com/OPSYS
 * ID=identifier:http://www.abbreviations.com/abbreviation/identifier */\
 ! defined TU_Bln361095cmnSrc_OpSys_Process_OpSysProcess_ID_prefix_h
   #define TU_Bln361095cmnSrc_OpSys_Process_OpSysProcess_ID_prefix_h

/**TU_Bln361095OpSysNmSpc,TU_Bln361095OpSysNmSpcBgn,TU_Bln361095OpSysNmSpcEnd*/
#include "../OpSys_ID_prefix.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095OpSysProcessDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]ProcessNmSpc".*/
  #define TU_Bln361095OpSysProcessNmSpc TU_Bln361095OpSysNmSpc ::\
    Process
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysProcessNmSpcBgn TU_Bln361095OpSysNmSpcBgn\
    namespace Process{
  #define TU_Bln361095OpSysProcessNmSpcEnd TU_Bln361095OpSysNmSpcEnd }
  #define TU_Bln361095OpSysProcessUse(suffix)\
    TU_Bln361095OpSysProcessNmSpc :: suffix
#else
///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095OpSysProcessDef(suffix)\
    TU_Bln361095OpSysDef(Process ## suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * "C" language has no namespaces->Replace with empty character string. */
  #define TU_Bln361095OpSysProcessNmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysProcessNmSpcBgn /** ->empty */
  #define TU_Bln361095OpSysProcessNmSpcEnd /** ->empty */
  #define TU_Bln361095OpSysProcessUse(suffix)\
    TU_Bln361095OpSysProcessDef(suffix)
#endif

#endif///Include guard
