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
 ! defined TU_Bln361095cmnSrc_OpSys_MS_Win_time_unifyTime_h
   #define TU_Bln361095cmnSrc_OpSys_MS_Win_time_unifyTime_h

///C,C++ standard library header files:
#include <time.h>///struct tm

///Microsoft Windows operating system header files:
#include <windows.h>///struct SYSTEMTIME, GetLocalTime(SYSTEMTIME)

///Stefan Gebauer's(TU Berlin mat.#361095) ~"common_sourcecode"repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
 ///TU_Bln361095OpSysDef, TU_Bln361095OpSysNmSpcBgn, TU_Bln361095OpSysNmSpcEnd
#include <OperatingSystem/OpSys_ID_prefix.h>

TU_Bln361095OpSysNmSpcBgn

TU_Bln361095frcInln void TU_Bln361095OpSysDef(UnifyTime)(
  SYSTEMTIME * p_systemTime,
  struct tm * p_tm)
{
  p_tm->tm_sec = p_systemTime->wSecond;
  p_tm->tm_min = p_systemTime->wMinute;
  p_tm->tm_hour = p_systemTime->wHour;
  p_tm->tm_wday = p_systemTime->wDayOfWeek;
  p_tm->tm_mday = p_systemTime->wDay;
  p_tm->tm_mon = p_systemTime->wMonth;
  p_tm->tm_yday = p_systemTime->wYear;
}

TU_Bln361095OpSysNmSpcEnd

#endif///include guard
