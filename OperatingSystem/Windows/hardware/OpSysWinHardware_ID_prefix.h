/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * File name should contain "OpSysWinHardware" to easier chose the correct file
 * if multiple "[...]ID_prefix.h" files are opened in an application.*/

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
 ! defined TU_Bln361095OpSys_Windows_hardware_OpSysWinHardware_ID_prefix_h
   #define TU_Bln361095OpSys_Windows_hardware_OpSysWinHardware_ID_prefix_h

/**TU_Bln361095hardwareNmSpc,
 * TU_Bln361095hardwareNmSpcBgn
 * TU_Bln361095hardwareNmSpcEnd */
#include "../OpSysWindows_ID_prefix.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095OpSysWindowsHardwareDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]HardwareNmSpc".*/
  #define TU_Bln361095OpSysWindowsHardwareNmSpc\
    TU_Bln361095OpSysWindowsNmSpc :: Hardware
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysWindowsHardwareNmSpcBgn\
    TU_Bln361095OpSysWindowsNmSpcBgn namespace Hardware{
  /**"}" times >>number of namespaces<<*/
  #define TU_Bln361095OpSysWindowsHardwareNmSpcEnd\
    TU_Bln361095OpSysWindowsNmSpcEnd }
  #define TU_Bln361095OpSysWindowsHardwareUse(suffix)\
    TU_Bln361095OpSysWindowsHardwareNmSpc :: suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095OpSysWindowsHardwareDef(suffix)\
    TU_Bln361095OpSysWindowsDef(Hardware ## suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
/**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095OpSysWindowsHardwareNmSpc /** ->empty */
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysWindowsHardwareNmSpcBgn /** ->empty */
  #define TU_Bln361095OpSysWindowsHardwareNmSpcEnd /** ->empty */
  #define TU_Bln361095OpSysWindowsHardwareUse(suffix)\
    TU_Bln361095OpSysWindowsHardwareDef(suffix)
#endif

#endif///Include guard