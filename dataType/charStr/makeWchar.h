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
 ! defined TU_Bln361095cmnSrc__dataType__charStr__makeWchar_h
   #define TU_Bln361095cmnSrc__dataType__charStr__makeWchar_h

///from https://stackoverflow.com/questions/14421656/is-there-widely-available-wide-character-variant-of-file
#define TU_Bln361095makeWchar_concat(x) L##x
#define TU_Bln361095charStrMakeWide(x) TU_Bln361095makeWchar_concat(x)

#endif///include guard
