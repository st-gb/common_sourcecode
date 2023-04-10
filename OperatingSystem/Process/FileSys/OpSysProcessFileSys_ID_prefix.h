/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * File name should contain "OpSysProcessFileSys" to easier chose the correct
 * file if multiple "[...]ID_prefix.h" files are opened in an application.*/

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
/**Include guard supported by (nearly) all compilers*/\
/**Bln=BerLiN: https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OPSYS
 * ID=IDentifier: http://www.abbreviations.com/abbreviation/identifier */\
 ! defined TU_Bln361095cmnSrc_OpSys_Process_OpSysProcessFileSys_ID_prefix_h
   #define TU_Bln361095cmnSrc_OpSys_Process_OpSysProcessFileSys_ID_prefix_h

/**TU_Bln361095OpSysProcessNmSpc, TU_Bln361095OpSysProcessNmSpcBgn,
 * TU_Bln361095OpSysProcessNmSpcEnd */
#include "../OpSysProcess_ID_prefix.h"

/**Use the following preprocessor macros in source code for example to enable
 * both C and C++.*/
#ifdef __cplusplus
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095OpSysProcessFileSysDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]ProcessNmSpc".*/
  #define TU_Bln361095OpSysProcessFileSysNmSpc\
     TU_Bln361095OpSysProcessNmSpc :: FileSys
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysProcessFileSysNmSpcBgn \
    TU_Bln361095OpSysProcessNmSpcBgn namespace FileSys{
  #define TU_Bln361095OpSysProcessFileSysNmSpcEnd\
    TU_Bln361095OpSysProcessNmSpcEnd }
  #define TU_Bln361095OpSysProcessFileSysUse(suffix)\
    TU_Bln361095OpSysProcessFileSysNmSpc :: suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095OpSysProcessFileSysDef(suffix)\
    TU_Bln361095OpSysProcessDef(FileSys ## suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
/**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095OpSysProcessFileSysNmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysProcessFileSysNmSpcBgn /** ->empty */
  #define TU_Bln361095OpSysProcessFileSysNmSpcEnd /** ->empty */
  #define TU_Bln361095OpSysProcessFileSysUse(suffix)\
    TU_Bln361095OpSysProcessFileSysDef(suffix)
#endif

#endif///include guard