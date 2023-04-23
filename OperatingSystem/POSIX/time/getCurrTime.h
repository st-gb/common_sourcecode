/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * File name comes from:
 * -Curr=CURRent: http://www.abbreviations.com/abbreviation/Current */

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
 * Curr=CURRent: http://www.abbreviations.com/abbreviation/Current */\
 ! defined TU_Bln361095cmnSrc_OpSys_POSIX_time_getCurrTime_h
   #define TU_Bln361095cmnSrc_OpSys_POSIX_time_getCurrTime_h

///C,C++ standard library header files:
#include <sys/time.h>///gettimeofday(...)
#include <string.h>///memcpy(...)

///Stefan Gebauer's(TU Berlin mat.#361095) ~"common_sourcecode"repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
 ///TU_Bln361095OpSysDef, TU_Bln361095OpSysNmSpcBgn, TU_Bln361095OpSysNmSpcEnd
#include <OperatingSystem/OpSys_ID_prefix.h>

TU_Bln361095OpSysNmSpcBgn

TU_Bln361095frcInln void TU_Bln361095OpSysDef(\
/**Curr=CURRent: http://www.abbreviations.com/abbreviation/Current */\
  GetCurrTime)(
  struct tm * p_tm_Current)
{
  static timeval timevalCurrentTime;
  /**see 
http://stackoverflow.com/questions/588307/c-obtaining-milliseconds-time-on-linux-clock-doesnt-seem-to-work-properly
   * answered Feb 25 '09 at 23:18 by "Jason Punyon" */
  static struct tm * p_tm;
    
  /**from http://www.gamedev.net/community/forums/topic.asp?topic_id=437062
   * ("best way to GetTickCount in Linux") /
http://www.linuxquestions.org/questions/programming-9/c-c-api-for-retrieving-system-time-in-micro-or-milliseconds-441519/
   */
  gettimeofday( & timevalCurrentTime,
  /** http://pubs.opengroup.org/onlinepubs/009604599/functions/gettimeofday.html
   * :"If tzp is not a null pointer, the behavior is unspecified." */ 0);
  /**see http://www.unix.com/programming/1991-time-microseconds.html
   * submitted by "Perderabo" on 09-04-2001 : */
  p_tm = localtime( & timevalCurrentTime.tv_sec ) ;
  /** http://www.cplusplus.com/reference/ctime/localtime/ :
  * "The returned value points to an internal object whose validity or value may
  * be altered by any subsequent call to gmtime or localtime."
  *  -> So make a copy. */
  memcpy(p_tm_Current, p_tm, sizeof(struct tm) );
}

TU_Bln361095OpSysNmSpcEnd

#endif///include guard
