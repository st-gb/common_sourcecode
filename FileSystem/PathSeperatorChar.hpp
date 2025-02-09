/**(c)Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095) */

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
/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc__FileSys__PathSepChar_h
   #define TU_Bln361095cmnSrc__FileSys__PathSepChar_h

///Stefan Gebauer's(TU Berlin matricul. num.361095) ~"cmnSrc" repository files:
 /**TU_Bln361095FileSysNmSpcBgn, TU_Bln361095FileSysNmSpcEnd,
  * TU_Bln361095FileSysDef(...)*/
 #include "FileSys_ID_prefix.h"
 ///TU_Bln361095MicroSoftWindows
 #include <OperatingSystem/Windows/MicrosoftWindows.h>

TU_Bln361095FileSysNmSpcBgn

  //static const char dirSeperatorChar;
#if defined(__linux__)
  const char TU_Bln361095FileSysDef(DirSepChar) = '/';
  const wchar_t TU_Bln361095FileSysDef(DirSepCharW) = L'/';///wide char version
#elif defined(TU_Bln361095MicroSoftWindows)
  const char TU_Bln361095FileSysDef(DirSepChar) = '\\';
  const wchar_t TU_Bln361095FileSysDef(DirSepCharW) = L'\\';///wide char version
#endif

TU_Bln361095FileSysNmSpcEnd

#endif///Include guard