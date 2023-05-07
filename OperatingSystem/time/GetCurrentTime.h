/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
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
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys 
 * MS=MicroSoft: http://www.abbreviations.com/abbreviation/MicroSoft
 * Win=WINdows: http://www.abbreviations.com/abbreviation/Windows */\
 ! defined TU_Bln361095cmnSrc_OpSys_time_getCurrTime_h
   #define TU_Bln361095cmnSrc_OpSys_time_getCurrTime_h

#ifdef _WIN32
  #include <OperatingSystem/Windows/time/getCurrTime.h>
#endif///Windows

#if defined( __unix__) //|| defined (__ANDROID__)
  #include <OperatingSystem/POSIX/time/getCurrTime.h>
#endif

#ifdef __cplusplus
TU_Bln361095OpSysNmSpcBgn

inline void GetCurrTime(struct tm& tm_Current)
{
  TU_Bln361095OpSysUse(GetCurrTime)(&tm_Current);
}
TU_Bln361095OpSysNmSpcEnd
#endif

#endif///include guard
