/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
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
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc_hardware_bus_busType_h
   #define TU_Bln361095cmnSrc_hardware_bus_busType_h

/**TU_Bln361095hardwareBusNmSpcBgn, TU_Bln361095hardwareBusNmSpcEnd
 * TU_Bln361095hardwareBusDef */
#include "hardwareBus_ID_prefix.h"

TU_Bln361095hardwareBusNmSpcBgn

enum TU_Bln361095hardwareBusDef(Type)
{
  TU_Bln361095hardwareBusDef(NVMe),
  TU_Bln361095hardwareBusDef(SATA),
  TU_Bln361095hardwareBusDef(USB),
  TU_Bln361095hardwareBusDef(Unset)
};

TU_Bln361095hardwareBusNmSpcEnd

#endif///include guard
