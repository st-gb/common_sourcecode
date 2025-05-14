///(c)from 2017:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
/**@author Stefan Gebauer:TU Berlin matriculation number 361095
 * Created on 4. Mai 2017, 12:28 */

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
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 * "OpSys"="OPerating SYStem" :
 *  https://www.abbreviations.com/abbreviation/Operating%20system */\
 ! defined TU_Bln361095cmnSrc__OpSys__multithread__nativeEvtTyp_hpp
   #define TU_Bln361095cmnSrc__OpSys__multithread__nativeEvtTyp_hpp

///Stefan Gebauer's(TU Berlin matricul.numb.361095) ~"cmnSrc" repository files:
 ///TU_Bln361095OpSysNmSpcBgn, TU_Bln361095OpSysNmSpcEnd
 #include "../OpSys_ID_prefix.h"

#ifdef __linux__ //TODO: change to ifdef POSIX
  #include <OperatingSystem/POSIX/multithread/Event.hpp>
  typedef pthread::Condition nativeEvent_type;
  TU_Bln361095OpSysNmSpcBgn
  /**"Evnt"="EVeNT": https://www.abbreviations.com/abbreviation/Event
   * "Typ"=TYPe": https://www.abbreviations.com/abbreviation/type */
  typedef pthread::Condition nativeEvntTyp;
  TU_Bln361095OpSysNmSpcEnd
#endif
#ifdef _WIN32
  #include <OperatingSystem/Windows/multithread/Win32EventBasedEvent.hpp>
  typedef Win32EventBasedEvent nativeEvent_type;
  TU_Bln361095OpSysNmSpcBgn
  /**"Evnt"="EVeNT": https://www.abbreviations.com/abbreviation/Event
   * "Typ"="TYPe": https://www.abbreviations.com/abbreviation/type */
  typedef Win32EventBasedEvent nativeEvntTyp;
  TU_Bln361095OpSysNmSpcEnd
#endif

#endif///include guard
