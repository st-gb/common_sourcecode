///(c)from 2025:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
/** @author Stefan Gebauer:TU Berlin matriculation number 361095*/

///Include guard, see http://en.wikipedia.org/wiki/Include_guard :

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
/**Bln=BerLiN: https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc__time__timeConstants_h
   #define TU_Bln361095cmnSrc__time__timeConstants_h

/**"Sec"="SECond": https://www.abbreviations.com/abbreviation/second
 * "Min"="MINute": https://www.abbreviations.com/abbreviation/minute */
#define TU_Bln361095timeSecsPerMin 60
#define TU_Bln361095timeSecsPerHour /*3600*/\
  /**Use brackets to use the macro in expression without side effects */\
  (TU_Bln361095timeSecsPerMin * 60)
///86400s=60s/min*60min/h*24h/d=3600s/h*24h=1 day
#define TU_Bln361095timeSecsPerDay /*86400*/\
  /**Use brackets to use the macro in expression without side effects*/\
  (TU_Bln361095timeSecsPerHour * 24)

#endif///include guard