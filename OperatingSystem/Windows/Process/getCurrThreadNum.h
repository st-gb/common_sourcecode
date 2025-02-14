/**File name "cmdLneArgs" comes from:CoMmanD LiNE ARGumentS
 * (c) from 2025 by Stefan Gebauer(Computer Science Master from TU Berlin)
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
 * curr=CURRent:http://www.abbreviations.com/term/2465521/current
 * Num=NUMber:http://www.abbreviations.com/term/157503/number */\
 ! defined TU_Bln361095cmnSrc__OpSys__Windows__Process__getCurrThreadNum_h
   #define TU_Bln361095cmnSrc__OpSys__Windows__Process__getCurrThreadNum_h

#ifdef _WIN32///Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)

///Microsoft Windows API header files:
 #include <windows.h>///::GetCurrentThreadId()

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 ///TU_Bln361095OpSysNmSpcBgn, TU_Bln361095OpSysNmSpcEnd, TU_Bln361095OpSysDef
 #include <OperatingSystem/OpSys_ID_prefix.h>
 #include <compiler/force_inline.h>///TU_Bln361095frcInln

TU_Bln361095OpSysNmSpcBgn

TU_Bln361095frcInln DWORD TU_Bln361095OpSysDef(GetCurrThreadNum)()
{
#ifdef _DEBUG
  DWORD dwCurrentThreadId = GetCurrentThreadId();
  return dwCurrentThreadId;
#else
  return GetCurrentThreadId();
#endif
}
TU_Bln361095OpSysNmSpcEnd

#endif///_WIN32
#endif///Include guard
