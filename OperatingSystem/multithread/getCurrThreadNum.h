/**(c) from 2013 by Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * Created on: 10.02.2013 */

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
/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPeratingSYStem:
 *  http://www.abbreviations.com/abbreviation/operating%20system */\
 ! defined TU_Bln361095cmnSrc__OpSys__Process__getCurrThreadNum_h
   #define TU_Bln361095cmnSrc__OpSys__Process__getCurrThreadNum_h

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 ///TU_Bln361095MicroSoftWindows
 #include <OperatingSystem/Windows/MicroSoftWindows.h>

#ifdef TU_Bln361095MicroSoftWindows
  ///DWORD TU_Bln361095OpSysUse(GetCurrThreadNum)()
  #include <OperatingSystem/Windows/Process/getCurrThreadNum.h>
#endif

#ifdef __linux__
  #include <OperatingSystem/Linux/GetCurrentThreadNumber.h>
  #include "preprocessor_macros/Windows_compatible_typedefs.h" //for DWORD
//  #ifndef DWORD
//    #define DWORD unsigned
//  #endif
#endif

#endif///Include guard
