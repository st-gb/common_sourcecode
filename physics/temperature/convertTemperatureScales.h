///(c) from 2025 Stefan Gebauer(Computer Science Master from TU Berlin)
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
/**Bln=Berlin:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=common:http://www.abbreviations.com/abbreviation/common
 * Src=source:http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc__physics__temperature__convertTemperatureScales_h
   #define TU_Bln361095cmnSrc__physics__temperature__convertTemperatureScales_h

///Stefan Gebauer's(TU Berlin matricul.number 361095) ~"cmnSrc"repository files:
 #include <ID_prefix.h>///TU_Bln361095cmnSrcDef(...)
 #include <compiler/force_inline.h>///TU_Bln361095frcInln
 #include <hardware/CPU/fastest_data_type.h>///TU_Bln361095CPUuse(faststUint)

TU_Bln361095nmSpcBgn

TU_Bln361095frcInln TU_Bln361095CPUuse(faststUint) TU_Bln361095def(
  KelvinToDegC)(
  const TU_Bln361095CPUuse(faststUint) valInDegC)
{
  return valInDegC
    /**Convert Kelvin to degrees Celsius by subracting the difference to
     * 0 �C (273.15 Kelvin). See http://en.wikipedia.org/wiki/Kelvin */
    - 273;
}

TU_Bln361095nmSpcEnd

#endif