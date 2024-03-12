///(c)from 2024 by Stefan Gebauer(Computer Science Master from TU Berlin)
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
/**Bln=Berlin:http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * char=CHARacter: http://www.abbreviations.com/abbreviation/character
 * Str=STRing: http://www.abbreviations.com/abbreviation/String */\
 ! defined TU_Bln361095cmnSrc__dataType__charStr__stringize_h
   #define TU_Bln361095cmnSrc__dataType__charStr__stringize_h

/**http://gcc.gnu.org/onlinedocs/gcc-8.5.0/cpp/Stringizing.html
 * "If you want to stringize the result of expansion of a macro argument, you
 *  have to use two levels of macros.
 *  #define xstr(s) str(s)
 *  #define str(s) #s
 *  #define foo 4
 *  str (foo)
 *       → "foo"
 *  xstr (foo)
 *       → xstr (4)
 *       → str (4)
 *       → "4"*/
/**http://gcc.gnu.org/onlinedocs/gcc-8.5.0/cpp/Stringizing.html
 * "s is stringized when it is used in str, so it is not macro-expanded first.
 *  But s is an ordinary argument to xstr, so it is completely macro-expanded
 *  before xstr itself is expanded (see Argument Prescan). Therefore, by the
 *  time str gets to its argument, it has already been macro-expanded."*/
#define TU_Bln361095expandAndStringize(charStr) TU_Bln361095stringize(charStr)
#define TU_Bln361095stringize(charStr) #charStr

#endif///Include guard
