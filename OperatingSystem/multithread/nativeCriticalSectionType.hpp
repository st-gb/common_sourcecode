/**(c) from 09.02.2013 by Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author: Stefan Gebauer(TU Berlin matriculation number 361095)*/

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
 *  http://www.abbreviations.com/abbreviation/operating%20system
 * Crit=CRITical:http://www.abbreviations.com/abbreviation/critical
 * Sec=SECtion:http://www.abbreviations.com/abbreviation/section
 * Typ=TYPe:http://www.abbreviations.com/abbreviation/Type */\
 ! defined TU_Bln361095cmnSrc__OpSys__multithread__nativeCritSecTyp_h
   #define TU_Bln361095cmnSrc__OpSys__multithread__nativeCritSecTyp_h

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 ///TU_Bln361095OpSysNmSpcBgn, TU_Bln361095OpSysNmSpcEnd
 #include <OperatingSystem/OpSys_ID_prefix.h>
 ///TU_Bln361095MicroSoftWindows
 #include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef TU_Bln361095MicroSoftWindows
  #include <OperatingSystem/Windows/multithread/CriticalSection.hpp>
  TU_Bln361095OpSysNmSpcBgn
  typedef OperatingSystem::Windows::CriticalSection nativeCriticalSection_type;
  TU_Bln361095OpSysNmSpcEnd
#endif

#ifdef __linux__ //TODO: change to ifdef POSIX
  #include <OperatingSystem/POSIX/multithread/pthread_Based_I_CriticalSection.hpp>
  TU_Bln361095OpSysNmSpcBgn
  typedef pthread_Based_I_CriticalSection nativeCriticalSection_type;
  TU_Bln361095OpSysNmSpcEnd
#endif

#endif///Include guard
