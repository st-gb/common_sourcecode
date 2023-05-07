///(c)Stefan Gebauer,Computer Science Master(TU Berlin,matric.number 361095)
///@author Stefan Gebauer(TU Berlin matriculation number 361095)

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
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc_OpSys_POSIX_suspendExec_h
   #define TU_Bln361095cmnSrc_OpSys_POSIX_suspendExec_h

///GCC/MinGW header files:
/**http://pubs.opengroup.org/onlinepubs/009696799/functions/sleep.html :
 * "#include <unistd.h>"*/
#include <unistd.h>///sleep(unsigned seconds);

///Stefan Gebauer's(TU Berlin mat.#361095)~"common_sourcecode" repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
#include <hardware/CPU/fastest_data_type.h>///TU_Bln361095CPUuse(FaststUint)
///TU_Bln361095OpSysDef, TU_Bln361095OpSysNmSpcBgn, TU_Bln361095OpSysNmSpcEnd
#include <OperatingSystem/OpSys_ID_prefix.h>

TU_Bln361095OpSysNmSpcBgn

TU_Bln361095frcInln void TU_Bln361095OpSysDef(
///Start with a capital letter for better readability if compiled as "C".
  SuspendExecInS)(const TU_Bln361095CPUuse(FaststUint) seconds)
{
  /** https://linux.die.net/man/3/sleep */
  sleep(seconds);
}

TU_Bln361095frcInln void TU_Bln361095OpSysDef(
///Start with a capital letter for better readability if compiled as "C".
  SuspendExecInMs)(const TU_Bln361095CPUuse(FaststUint) milliSeconds)
{
  ///Sleep in microseconds (1/1000th of a millisecond))
  usleep(milliSeconds * 1000);
}

TU_Bln361095OpSysNmSpcEnd

#endif///include guard
