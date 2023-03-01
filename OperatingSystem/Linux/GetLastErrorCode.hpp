/**(c) Stefan Gebauer(TU Berlin matriculation number:361095)
 * Created on: Sep 9, 2010
 * @author Stefan Gebauer(Computer Science Master from TU Berlin)*/

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
/**cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem:http://www.abbreviations.com/OPSYS */\
 ! defined TU_Bln361095cmnSrcOpSysLinuxGetLastErrorCode_h
   #define TU_Bln361095cmnSrcOpSysLinuxGetLastErrorCode_h

#include <errno.h> //for "errno"

/**TU_Bln361095cmnSrcOpSysDef,TU_Bln361095cmnSrcOpSysNmSpcBgn,
 * TU_Bln361095cmnSrcOpSysNmSpcEnd */
#include "../ID_prefix.h"
#include <compiler/force_inline.h>///TU_Bln361095frcInl

TU_Bln361095cmnSrcOpSysNmSpcBgn

/** Make the function inline (->no function overhead/ call stack->faster)
* because it includes just 1 instruction->we would not save space in the exe
* if it was a real function with a call stack. */
TU_Bln361095frcInl /*DWORD*/ unsigned long int TU_Bln361095cmnSrcOpSysDef(
  GetLastErrorCode)()
{
  return errno;
}

TU_Bln361095cmnSrcOpSysNmSpcEnd

#endif///Include guard
